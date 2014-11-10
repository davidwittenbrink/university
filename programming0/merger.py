import sys
import re
from hashlib import sha256

def calculate_overhead(old_length, new_length):
	"Calcutlates overhead given two lengths."
	return int( (old_length - new_length) / new_length  * 100 )

def matching_hashsum(file1, file2):
	"Returns true if file1 sha256 sum matches the one given in file 2."
	return sha256(file1).hexdigest() == file2

def merger():
	""" Merges a 'input.txt' (or file given as param1) containing text messages seperated by
		dividing lines and stores result in 'output.txt' or file given as param2. Also checks
		for sha256 sum of output file with 'checksum.dat' and generates a 'statistik.txt' file."""

	input_file_name  = sys.argv[1] if len(sys.argv) > 1 else "input.txt"
	output_file_name = sys.argv[2] if len(sys.argv) > 2 else "output.txt"
	
	with open(input_file_name, 'r') as input_file, open(output_file_name, 'w') as output_file:
		file_content = input_file.read()
		texts = [t for t in re.split(r'\([0-9]*\/160\)\n-{60}\n?', file_content) if t] # filter out None and ''
		new_file_content = ''.join(texts)
		output_file.write(new_file_content)

	with open(output_file_name, 'rb') as output_file,   \
		 open('checksum.dat',   'r')  as checksum_file, \
		 open('statistik.txt',  'w')  as stats_file:
		
		stats = {"sms_count"       : len(texts),
				 "full_length"     : len(file_content),
				 "new_length"      : len(new_file_content),
				 "overhead"		   : calculate_overhead(len(file_content), len(new_file_content)) if texts else 0,
				 "correct_checksum": "ja" if matching_hashsum(output_file.read(), checksum_file.read()) else "nein"}

		stats_file.write(("Anzahl SMS: {sms_count}\n"
										  "Anzahl Zeichen gesplittet: {full_length}\n"
										  "Anzahl Zeichen zusammengeführt: {new_length}\n"
										  "Overhead: {overhead}%\n"
										  "Checksum korrekt: {correct_checksum}").format(**stats))

if __name__ == '__main__':
	merger()