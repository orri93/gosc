#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#include <xopt.h>

#include <gos/types.h>
#include <gos/noise.h>
#include <gos/signal.h>
#include <gos/geometry.h>
#include <gos/interpolate.h>
#include <gos/version.h>

#define DEFAULT_PROGNAME   "generator"
#define ERR_FOPEN_OUTPUT   "fopen(output, w)"
#define LONG_OPTIONS_COUNT  4

typedef struct gos_example_generator_data {
  double* data;
  double* depth;
  gos_range_1d data_range;
  gos_range_1d depth_range;
  int count;
} gos_example_generator_data;

typedef struct gos_example_generator_context {
  int count;
  gos_example_generator_data** data;
  FILE* output;
  FILE* file;
} gos_example_generator_context;

typedef struct gos_example_generator_settings {
  bool help;
  bool version;
  int toolcount;
  int datapointcount;
  int majorcount;
  const char* outputfn;
} gos_example_generator_settings;

xoptOption options[LONG_OPTIONS_COUNT] = {
  {
    "help",
    'h',
    offsetof(gos_example_generator_settings, help),
    0,
    XOPT_TYPE_BOOL,
    0,
    "produce help message"
  },
  {
    "version",
    'v',
    offsetof(gos_example_generator_settings, version),
    0,
    XOPT_TYPE_BOOL,
    0,
    "print version string"
  },
  {
    "output",
    'o',
    offsetof(gos_example_generator_settings, outputfn),
    0,
    XOPT_TYPE_STRING,
    "s",
    "output file name"
  },
  {
    "tool-count",
    't',
    offsetof(gos_example_generator_settings, toolcount),
    0,
    XOPT_TYPE_INT,
    "n",
    "tool count"
  }
};

static bool gos_example_generator_initialize(
  gos_example_generator_settings* settings,
  gos_example_generator_context* context);

static bool gos_example_generator_generate(
  gos_example_generator_data* data,
  gos_generation_1d* datageneration,
  gos_generation_1d* depthgeneration,
  int major);

static void gos_example_generator_output(
  gos_example_generator_settings* settings,
  gos_example_generator_context* context);

static void gos_example_generator_output_header(
  gos_example_generator_settings* settings,
  FILE* output);

static void gos_example_generator_output_data(
  gos_example_generator_data* data,
  FILE* output,
  int at);

static void gos_example_generator_shutdown(
  gos_example_generator_context* context);

int main(int argc, char* argv[]) {
  int mainresult, extracount;

  const char* xopterr;
  char** xoptextras;

  xoptContext* xoptctx;
  xoptAutohelpOptions xopthelpo;
  gos_example_generator_settings settings = {
    false,  /* help */
    false,  /* version */
    4,      /* tool count */
    1024,   /* data point count */
    64,     /* major count */
    NULL    /* output file name */
  };
  gos_example_generator_context context = {
    0,      /* count */
    NULL,   /* data */
    stdout, /* output */
    NULL    /* file */
  };

  mainresult = EXIT_SUCCESS;
  xoptextras = NULL;
  xoptctx = NULL;

  /* Create options context */
  xoptctx = xopt_context(
    DEFAULT_PROGNAME,
    options,
    XOPT_CTX_POSIXMEHARDER | XOPT_CTX_STRICT,
    &xopterr);
  if (xopterr) {
    fprintf(stderr, "Error: %s\n", xopterr);
    goto gosc_example_generator_exit_failure;
  }

  /* Parse options */
  extracount = xopt_parse(
    xoptctx,
    argc,
    argv,
    &settings,
    &xoptextras,
    &xopterr);
  if (xopterr) {
    fprintf(stderr, "Error: %s\n", xopterr);
    goto gosc_example_generator_exit_failure;
  }

  /* Handle help */
  if (settings.help) {
    xopthelpo.usage = "[options] [extras...]";
    xopthelpo.prefix = "GOS C Library Generator Example.";
    xopthelpo.suffix = "End argument list.";
    xopthelpo.spacer = 10;
    xopt_autohelp(xoptctx, stderr, &xopthelpo, &xopterr);
    goto gosc_example_generator_exit_failure;
  }

  /* Handle version */
  if (settings.version) {
    fprintf(
      stderr,
      "GOS C Library Generator Example version %s",
      GOSC_VERSION_STRING);
    goto gosc_example_generator_exit_failure;
  }

  /* Handle output */
  if (settings.outputfn != NULL) {
    context.file = fopen(settings.outputfn, "w+");
    if (context.file != NULL) {
      context.output = context.file;
    } else {
      perror(ERR_FOPEN_OUTPUT);
      goto gosc_example_generator_exit_cleanup;
    }
  }

  /* The Generation and output */
  if (gos_example_generator_initialize(&settings, &context)) {
    gos_example_generator_output(&settings, &context);
    gos_example_generator_shutdown(&context);
  } else {
    goto gosc_example_generator_exit_failure;
  }

  /* Exiting */
  goto gosc_example_generator_exit_cleanup;

gosc_example_generator_exit_failure:
  mainresult = EXIT_FAILURE;

gosc_example_generator_exit_cleanup:
  if (context.file != NULL) {
    fclose(context.file);
  }
  if (xoptextras) {
    free(xoptextras);
  }
  if (xoptctx) {
    free(xoptctx);
  }
  return mainresult;
}

bool gos_example_generator_initialize(
  gos_example_generator_settings* settings,
  gos_example_generator_context* context) {
  int i;
  gos_range_1d depth;
  gos_example_generator_data** datastat;
  gos_generation_1d datageneration, depthgeneration;

  size_t datapointsize;

  bool result;

  context->count = 0;
  context->data = NULL;

  double datastart = 1.5;
  double datastep = 8.0;
  double datavar = 1.0;

  double depthspace = 100.0;

  depth.from = 50.0;
  depth.to = 100.0;

  datageneration.noise = 0.01;
  depthgeneration.noise = 0.01;

  datapointsize = settings->datapointcount * sizeof(double);

  if (settings->majorcount < settings->datapointcount) {
    context->data = (gos_example_generator_data**)calloc(
      settings->toolcount, sizeof(gos_example_generator_data*));
    if (context->data != NULL) {
      datastat = context->data;
      context->count = settings->toolcount;
      for (i = 0; i < settings->toolcount; i++) {

        datageneration.range.from = datastart - datavar + datastep * i;
        datageneration.range.to = datastart + datavar + datastep * i;

        depthgeneration.range.from = depth.from + depthspace * i;
        depthgeneration.range.to = depth.to + depthspace * i;

        *datastat = (gos_example_generator_data*)malloc(
          sizeof(gos_example_generator_data));
        if ((*datastat) != NULL) {
          (*datastat)->count = 0;
          (*datastat)->data = (*datastat)->depth = NULL;
          (*datastat)->data = (double*)malloc(datapointsize);
          if ((*datastat)->data != NULL) {
            (*datastat)->depth = (double*)malloc(datapointsize);
            if ((*datastat)->depth != NULL) {
              (*datastat)->count = settings->datapointcount;
              result = gos_example_generator_generate(
                (*datastat),
                &datageneration,
                &depthgeneration,
                settings->majorcount);
              if (result) {
                datastat++;
              } else {
                gos_example_generator_shutdown(context);
                fprintf(stderr, "Failed to generate data for tool no. %d", i);
                return false;
              }
            } else {
              gos_example_generator_shutdown(context);
              fprintf(
                stderr,
                "Out of memory while creating depth data points");
              return false;
            }
          } else {
            gos_example_generator_shutdown(context);
            fprintf(stderr, "Out of memory while creating data points");
            return false;
          }
        } else {
          gos_example_generator_shutdown(context);
          fprintf(
            stderr,
            "Out of memory while creating simulated data structure");
          return false;
        }
      }
    } else {
      gos_example_generator_shutdown(context);
      fprintf(stderr, "Out of memory while creating simulated data array");
      return false;
    }
  } else {
    gos_example_generator_shutdown(context);
    fprintf(stderr, "Major count is grater than data point count");
    return false;
  }
  return true;
}

bool gos_example_generator_generate(
  gos_example_generator_data* data,
  gos_generation_1d* datageneration,
  gos_generation_1d* depthgeneration,
  int major) {

  int div, i, j, n, e;

  double dat, dep;
  double depth, depthdistance, depthstep;
  double y0, y1, y2, y3;
  double mu, ms;

  double* v;
  double* vat;

  assert(data != NULL);
  assert(major < data->count);

  data->data_range.from = DBL_MAX;
  data->data_range.to = -DBL_MAX;
  data->depth_range.from = DBL_MAX;
  data->depth_range.to = -DBL_MAX;

  depth = depthgeneration->range.from;
  depthdistance = gos_geometry_distance_1d(&(depthgeneration->range));
  depthstep = depthdistance / (double)(data->count);

  e = data->count % major == 0 ? major + 3 : major + 4;
  v = vat = (double*)malloc(e * sizeof(double));

  if (v != NULL) {
    gos_signal_generate_range_random_y(v, e,
      datageneration->range.from,
      datageneration->range.to);

    div = data->count / major;
    ms = 1.0 / div;

    n = 0;
    for (i = 2; i < e - 1 && n < data->count; i++) {
      mu = 0.0;
      y0 = v[i - 2];
      y1 = v[i - 1];
      y2 = v[i];
      y3 = v[i + 1];

      for (j = 0; j < div && n < data->count; j++) {
        assert(n < data->count);
        assert(mu < 1.0);
        dat = gos_interpolate_cubic_catmull_rom(y0, y1, y2, y3, mu) +
          datageneration->noise *
          gos_noise_white(GOS_NOISE_DEFAULT_SEED, i, j);
        if (dat < data->data_range.from) {
          data->data_range.from = dat;
        }
        if (dat > data->data_range.to) {
          data->data_range.to = dat;
        }
        data->data[n] = dat;

        dep = depth + depthgeneration->noise *
          gos_noise_white(GOS_NOISE_DEFAULT_SEED, i, j);
        if (dep < data->depth_range.from) {
          data->depth_range.from = dep;
        }
        if (dep > data->depth_range.to) {
          data->depth_range.to = dep;
        }
        data->depth[n] = dep;
        depth += depthstep;
        mu += ms;
        n++;
      }
    }
    assert(n == data->count);

    free(v);

    return true;
  }
  else {
    return false;
  }
}

void gos_example_generator_output(
  gos_example_generator_settings* settings,
  gos_example_generator_context* context) {
  int i, j;
  gos_example_generator_data* data;
  gos_example_generator_output_header(settings, context->output);
  for (i = 0; i < settings->datapointcount; i++) {
    fprintf(context->output, "\n%d", i);
    for (j = 0; j < settings->toolcount; j++) {
      data = context->data[j];
      assert(data->count == settings->datapointcount);
      gos_example_generator_output_data(data, context->output, i);
    }
  }
}

void gos_example_generator_output_header(
  gos_example_generator_settings* settings,
  FILE* output) {
  int i;
  fprintf(output, "n");
  for (i = 0; i < settings->toolcount; i++) {
    fprintf(output, ",td%d,tv%d", i, i);
  }
}

void gos_example_generator_output_data(
  gos_example_generator_data* data, FILE* output, int at) {
  fprintf(output, ",%f,%f", data->depth[at], data->data[at]);
}

void gos_example_generator_shutdown(gos_example_generator_context* context) {
  int i;
  gos_example_generator_data* datastr;
  if (context != NULL) {
    if (context->data != NULL) {
      for (i = 0; i < context->count; i++) {
        if (context->data[i] != NULL) {
          datastr = context->data[i];
          if (datastr->data != NULL) {
            free(datastr->data);
            datastr->data = NULL;
          }
          if (datastr->depth != NULL) {
            free(datastr->depth);
            datastr->depth = NULL;
          }
        }
      }
      free(context->data);
      context->data = NULL;
      context->count = 0;
    }
  }
}
