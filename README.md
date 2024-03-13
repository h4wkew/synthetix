# synthetix

synthetix is a tool designed to generate customized wordlists for use in various security, development, and testing applications. It offers a wide range of customization options to create highly targeted and effective wordlists based on specific character sets, and rules.

## Installation

1. Clone the repository:
```bash
git clone https://github.com/h4wkew/synthetix.git
```

2. Navigate to the project directory:
```bash
cd synthetix
```

3. Build the application
```bash
bash run.sh
```

## Usage

To use synthetix, run the application with your desired format file. Here is a basic example:

```bash
./synthetix -f example.synx
```

In this command, -f flags the input of your format file, and `example.synx` represents the file containing your custom wordlist generation parameters. Simply replace it with the path to your own format file to generate wordlists tailored to your specific needs.

## How it works ?

synthetix generate wordlist from a custom wordlist generation parameters file with the `.synx`.

### Basic Structure of .synx File

Each line in the .synx file could be referred to as a **segment definition** since each line defines how a segment of the wordlist entry is generated.

Each segment followed this specific pattern: `LENGTH;TYPE;RULE`.

### Components Explained

#### Length

Indicates the number or range of characters for a segment.

| Pattern  |                             Description                            |
| -------- | ------------------------------------------------------------------ |
| n        | Generates exactly `n` characters, where n is a positive integer.   |
| x-z      | Generates between `x` to `z` characters, inclusively.              |
| *        | Places a fixed string.                                             |

#### Type

Defines the type of characters to be included, it could be a fixed string or a set of character

| Set  |             Description            |
| -------- | ---------------------------------- |
| letter   | Both uppercase and lowercase letters (A-Z, a-z). |
| upper    | Only uppercase letters (A-Z). |
| lower    | Only lowercase letters (a-z). |
| digit    | Digits (0-9). |
| even     | Even digits (0, 2, 4, 6, 8). |
| odd      | Odd digits (1, 3, 5, 7, 9). |
| special  | Special characters (e.g., @, #, $). |
| all      | All ASCII characters .|

Sets can be combined with + to include multiple sets or - to exclude specific sets. (e.g., all-digit to use all characters except digits).

#### Rule (optional)

This parameter provides further control over the generated output by allowing the inclusion or exclusion of specific characters or patterns:

|  Pattern  |                                Description                              |
| --------- | ----------------------------------------------------------------------- |
| [abc]     | Includes the specified characters (e.g., a, b, c).                 |

To exclude specific characters or ranges, precede the pattern with a `!`. For example, **![abc]** excludes the characters a, b, and c from the generated output.

## Example of a .synx file

```
3;letter;
2;digit;![45]
1;special;[01]
*;test
```

Sequences (linen) indicate that each wordlist entry should has :
- Three letter (a-z and A-Z).
- Two digits, exluding 4 and 5.
- One character that is either special or the digit 0 or 1.
- Fixed string "test".

## Understanding the Output

An entry in the wordlist following the above rules could be **abc12#test**:

`abc` for the first three letters.
`12` for two digits which are not 4 or 5.
`#` as a special character.
`test` as the fixed string appended at the end.

Other valid entry could be : vak670test, dfv00!test, apm16%test.

For further examples and advanced usage, refer to the `examples` directory in the project repository.