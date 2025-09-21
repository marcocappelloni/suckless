#!/bin/bash

CACHE_FILE="/tmp/cpu_usage_cache.txt"
# Run the color script and capture its output
FG_COLOR=$(get_xresource_color "color3")
DEFAULT_COLOR=$(get_xresource_color "foreground")

# Read cached values or initialize
if [[ -f "$CACHE_FILE" ]]; then
  mapfile -t cached <"$CACHE_FILE"
  old_time="${cached[0]}"
  old_total="${cached[1]}"
  old_idle="${cached[2]}"
else
  old_time=0
  old_total=0
  old_idle=0
fi

# Get current time and CPU stats
cur_time=$(date +%s)
total=0
idle=0

# Parse /proc/stat
while IFS= read -r line; do
  if [[ $line == cpu\ * ]]; then
    set -- $line
    # Sum all time fields (user, system, idle, etc.)
    for i in {2..8}; do
      total=$((total + ${!i}))
    done
    idle=$5 # $5 is the idle field (third column after 'cpu')
    break
  fi
done </proc/stat

# Save current values for next run
echo -e "$cur_time\n$total\n$idle" >"$CACHE_FILE"

# Avoid calculating on first run
if [[ "$old_time" -eq 0 ]]; then
  echo "CPU: --%"
  exit 0
fi

# Time difference in seconds
time_diff=$((cur_time - old_time))

# Avoid division by zero or too-frequent runs
if [[ "$time_diff" -lt 1 ]]; then
  echo "CPU: --%"
  exit 0
fi

# Calculate deltas
total_diff=$((total - old_total))
idle_diff=$((idle - old_idle))

# Avoid division by zero
if [[ "$total_diff" -eq 0 ]]; then
  echo "CPU: 0%"
  exit 0
fi

# Calculate CPU usage percentage
usage=$(((total_diff - idle_diff) * 100 / total_diff))

echo "^c$FG_COLOR^CPU: ${usage}%^c$DEFAULT_COLOR^"
