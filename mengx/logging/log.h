// Copyright (c) 2022 MengX
// Author: 1542978973@qq.com

#include <atomic>
#include <fstream>
#include <string>

namespace logging {
class Log {
 public:
  enum Level { Debug = 0, Info, Warn, Error };
  static Log* Instance() {
    static Log single;
    return &single;
  }

  static Log& Out(Level level);

  template <typename T>
  Log& operator<<(T&& Log);

 private:
  Log() : level_(0), f_("/var/log/mengx") {}
  ~Log() { f_.Close(); }

  template <typename T>
  void Writer(T&& Log, int level);

 private:
  std::atomic<Level> level_;
  fstream f_;
};

Log& Log::Out(Level level) {
  level_ = level;
  return *Instance();
}

template <typename T>
Log& Log::operator<<(T&& Log) {
  Writer(Log, level_);
  return *Instance();
}

void Log::Writer(T&& log, int level) {
  switch (level) {
    case Debug: {
      f_ << "Debug: ";
      break;
    }
    case Info: {
      f_ << "Info: ";
      break;
    }
    case Warn: {
      f_ << "Warn: ";
      break;
    }
    case Error: {
      f_ << "Error: ";
      break;
    }
  }
  f_ << log << "\n";
}

}  // namespace logging
