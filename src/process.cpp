#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// constructor for Process Class
Process::Process(int pid) {
  pid_ = pid;
  user_ = LinuxParser::User(pid_);
  command_ = LinuxParser::Command(pid_);
};

// DONE: Return this process's ID
int Process::Pid() { return pid_; }

// DONE: Return this process's CPU utilization
float Process::CpuUtilization() {
  long jiffies_start, jiffies_end;
  long uptime_start, uptime_end, delta;

  jiffies_start = LinuxParser::ActiveJiffies(pid_);
  uptime_start = LinuxParser::UpTime(pid_);
  // Wait 100ms
  usleep(100000);  // in microseconds

  jiffies_end = LinuxParser::ActiveJiffies(pid_);
  uptime_end = LinuxParser::UpTime(pid_);

  delta = uptime_end - uptime_start;
  // if delta is 0, it means the process doesn't use
  // the CPU anymore
  if (delta == 0) {
    return 0;
  }

  return (float)(jiffies_end - jiffies_start) /
         (float)(uptime_end - uptime_start);
}

// DONE: Return the command that generated this process
string Process::Command() { return command_; }

// DONE: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// DONE: Return the user (name) that generated this process
string Process::User() { return user_; }

// DONE: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// DONE: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  long ram = stol(LinuxParser::Ram(pid_));
  long ram_a = stol(LinuxParser::Ram(a.pid_));

  if (ram > ram_a) {
    return true;
  }

  return false;
}