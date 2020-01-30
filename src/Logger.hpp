#ifndef boxcar_logger_hpp
#define boxcar_logger_hpp

#include <string>

namespace BoxCar {
namespace Logging {
/**
 * Severity levels of logging events.
 * @author RailRunner16
 */
enum class LogSeverity {
    DBG,
    INF,
    WRN,
    ERR,
    FTL,
};

/**
 * A logger implementation.
 * @author RailRunner16
 */
class Logger {
  public:
    /**
     * Log an error message.
     * @param message The message.
     */
    static void err(std::string message);

    /**
     * Log an information message.
     * @param message The message.
     */
    static void inf(std::string message);

  private:
    static void internalLog(LogSeverity severity, const std::string& message);
};
}
}

#endif
