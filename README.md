# AutoQuick

> **Notice**: We are currently extending the application by implanting QML to create a modern graphical user interface.

AutoQuick is a utility application that automatically manages your Quick Access files and folders based on your timetable.
It adds and removes items from Quick Access at start of the computer start to keep your workspace organized and relevant to your today's schedule.

## Features

- 📅 **Timetable-Based Automation**: Load your schedule from a CSV file
- 📌 **Smart Quick Access Management**: Automatically add/remove files and folders based on current class
- ⚡ **Built with C++**: Fast and efficient performance

## Getting Started

### Prerequisites

- C++ compiler (C++17 or higher)
- Windows OS (for Quick Access integration)

### Installation

1. Clone the repository
2. Compile the project
3. Configure your timetable CSV file

### CSV Format

Starting AutoQuick will create a 'timetable.csv' at installed location if it is not present.
Edit the 'timetable.csv' file with the following format (INCLUDE HEADER):

```
day|class|path
Mon|Math|C:\path\to\math\notes
Tues|Physics|C:\path\to\physics\lab
```
Sunday -> Sun
Monday -> Mon
Tuesday -> Tue
Wednesday -> Wed
Thursday -> Thu
Friday -> Fri
Saturday -> Sat
Sunday ~ Saturday -> All
weekday -> wday
weekend -> wend

### Usage

```bash
AutoQuick.exe --config timetable.csv
```

## help

Usage: AutoQuick.exe [options]

Options:
  -h, --help                              Show help message\n"
  -v, --version                           Display application version\n"
  -c, --config <path>                     Path to timetable.csv\n"
  -s, --set                               Refreshes quick access\n"
  -r, --reset                             Resets quick access to default\n"
  -a, --add <day> <className> <path>      adds <day> and <path> to config\n"
  -rm, --remove <day> <className> <path>  removes <day> and <path> from config\n"

## License

MIT