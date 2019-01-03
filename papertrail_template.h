// See https://github.com/barakwei/ParticlePapertrail for setup information
// See https://docs.particle.io/reference/firmware/#logging for the firmware Logging API
#include "papertrail.h"

// We do logging via papertrail
PapertrailLogHandler papertailHandler("logsX.papertrailapp.com", portnumfromconsole, "appname");
