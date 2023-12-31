# mgiver
Simple archiver for `FASTQ` files. It using Huffman's algorithm to encode/decode files.

# Usage

## Compilation

To compile the program just type `make` in work directory.

## Encoding

To encode `fq` file type:

```
./mgiver.out -e -i fasta.fq -o arch -v
```

`arch`-folder will appear.

## Decoding

To decode `fq` file type:

```
./mgiver.out -i arch -v -d > result.fq
```

**NB**: you have to write `arch` _without_ slash (`/`);

**NB**: result `fq` file prints to the stdout.

## Parameters

- `-i` - input `fq`-file in encode / `arch`-folder in decode 
0 `-o` - `arch`-folder
- `-v` - verbose;
- `-e` - encode `fq`-file
- `-d` - decode `arch`-folder

# TODO

- [ ] Collect all files 
    - [x] Collect of all files to one directory
- [x] Implement [Huffman's coding](https://en.wikipedia.org/wiki/Huffman_coding) algorithm
  - [x] Use `bitset` 
  - [ ] Fix decompression time
- [ ] Implement **range coding**-algorithm
- [ ] Implement **ANS**-algorithm
- [ ] Add choice of what FASTQ-file's part encode with what algorithm
