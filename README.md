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

To use synthetix, run the application with your desired pattern file. Here is a basic example:

```bash
./synthetix -f example.synx
```

Here, `-f` specifies the pattern file (example.synx) that contains your wordlist generation parameters. Replace **example.synx** with the path to your custom format file.

## How It Works

synthetix generate wordlist from a custom pattern file with the `.synx` extension.

### Basic Structure of .synx File

A `.synx` file describes a **pattern** for generating wordlist entries, with each line representing one or more **block**.

Each line followed this specific pattern: `LENGTH;TYPE;RULE`.

### Components Explained

#### Length

Specifies the number or range of characters for a block:

| Pattern  |                             Description                            |
| -------- | ------------------------------------------------------------------ |
| n        | Generates exactly `n` characters, where n is a positive integer.   |
| x-z      | Generates between `x` to `z` number of characters, inclusively.              |
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

To exclude characters, prefix the pattern with ! (e.g., ![abc]).

## Example of a .synx file

```
3;letter;
2;digit;![45]
1;special;[01]
*;test
```

This pattern dictates that each wordlist entry will contain:

- Three letters (either uppercase or lowercase).
- Two digits, excluding '4' and '5'.
- One special character or the digits '0' or '1'.
- The fixed string "test" appended at the end.

## Understanding the Output

A wordlist entry conforming to the above rules could be **abc12#test** :

`abc` as the first three letters.
`12` as two digits, excluding 4 and 5.
`#` as a special character.
`test` as the fixed string appended at the end.

Other possible entries include: *vak670test*, *dfv00!test*, *apm16%test*.

Explore the examples directory in the project repository for more examples and advanced usage.