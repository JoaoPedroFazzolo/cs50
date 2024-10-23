from cs50 import get_string


def count_letters(text):
    count = sum(1 for char in text if char.isalpha())
    return count


def count_words(text):
    count = len(text.split())
    return count


def count_sentences(text):
    count = sum(1 for char in text if char in ['.', '!', '?'])
    return count


def main():
    text = get_string("Text: ")
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)
    L = (100.0 / words) * letters
    S = (100.0 / words) * sentences
    index = 0.0588 * L - 0.296 * S - 15.8
    index = round(index)
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {int(index)}")


if __name__ == "__main__":
    main()
