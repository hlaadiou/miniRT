import sys

def adjust_radius(input_file, output_file, radius_adjustment):
    try:
        with open(input_file, 'r') as infile, open(output_file, 'w') as outfile:
            for line in infile:
                parts = line.split()
                if len(parts) >= 4 and parts[0] == 'sp':
                    position = parts[1]
                    radius = float(parts[2])
                    color = parts[3]
                    new_radius = radius + radius_adjustment
                    new_line = f"{parts[0]} {position} {new_radius:.3f} {color}\n"
                    outfile.write(new_line)
                else:
                    # Handle lines that do not match the expected format
                    outfile.write(line)
        print(f"Radius adjusted by {radius_adjustment} and written to {output_file}")
    except Exception as e:
        print(f"An error occurred: {e}")

# Example usage
if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python adjust_radius.py <input_file> <output_file> <radius_adjustment>")
    else:
        input_file = sys.argv[1]
        output_file = sys.argv[2]
        radius_adjustment = float(sys.argv[3])
        adjust_radius(input_file, output_file, radius_adjustment)
