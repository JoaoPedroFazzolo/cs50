import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Uso: python script.py arquivo1.py arquivo2.py")
        sys.exit(1)
    database_doc = sys.argv[1]
    sequence_doc = sys.argv[2]

    # TODO: Read database file into a variable
    database = []
    with open(database_doc) as db:
        reader = csv.DictReader(db)
        for row in reader:
            database.append(row)

    # TODO: Read DNA sequence file into a variable
    with open(sequence_doc) as seq_file:
        dna_sequence = seq_file.read()

    # TODO: Find longest match of each STR in DNA sequence
    match_found = False
    for individual in database:
        if is_match(dna_sequence, individual):
            print(individual['name'])
            match_found = True
            break
    if not match_found:
        print("No match")


def is_match(sequence, individual):
    for str_name, str_count in individual.items():
        if str_name == 'name':
            continue
        if str_count != str(longest_match(sequence, str_name)):
            return False
    return True


def longest_match(sequence, subsequence):
    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
