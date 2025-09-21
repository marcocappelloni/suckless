#!/bin/bash
# In your ~/.local/bin/click_block.sh script

# Run the color script and capture its output
FG_COLOR=$(get_xresource_color "color4")
DEFAULT_COLOR=$(get_xresource_color "foreground")

# Used RAM in megabyte
used=$(free -mt | awk '/^Total:/ {print $3}')
# Total RAM
total=$(free -mt | awk '/^Total:/ {print $2}')

percentage=$((used * 100 / total))

echo "^c$FG_COLOR^RAM: $((percentage))%^c$DEFAULT_COLOR^"
