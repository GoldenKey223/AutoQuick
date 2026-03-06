# AutoQuick

AutoQuick is a utility application that automatically manages your Quick Access files and folders based on your school timetable. It intelligently adds and removes items from Quick Access throughout the day to keep your workspace organized and relevant to your current classes.

## Features

- 📅 **Timetable-Based Automation**: Load your schedule from a CSV file
- 📌 **Smart Quick Access Management**: Automatically add/remove files and folders based on current class
- ⚡ **Built with C++**: Fast and efficient performance
- 🔄 **Real-Time Updates**: Syncs with your timetable throughout the day

## Getting Started

### Prerequisites

- C++ compiler (C++17 or higher)
- Windows OS (for Quick Access integration)

### Installation

1. Clone the repository
2. Compile the project
3. Configure your timetable CSV file

### CSV Format

Create a `timetable.csv` file with the following format:

```
Time,Class,FilePath1,FilePath2,...
08:00,Math,C:\path\to\math\notes
10:00,Physics,C:\path\to\physics\lab
```

### Usage

```bash
AutoQuick.exe --config timetable.csv
```

## Configuration

Edit your CSV file to specify:
- Class start times
- Associated folders/files for each class
- Duration of each class

## License

MIT
