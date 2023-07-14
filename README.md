# mgiver
Simple archiver. It using Huffman's algorithm to encode/decode files.

# Usage

## Compilation

To compile the program just type `make` in work directory.

## Encoding

To encode `fq` file type:

```
./mgiver.out -e fasta.fq
```

Several files will appear, with `mgiver` in the name.

## Decoding

To decode `fq` file type (for expample there are `mgiver` files with prefix `fasta.fq`):

```
./mgiver.out -d fasta.fq > result.fq
```

**NB**: result `fq` file prints to the stdout.

# TODO

- [x] Implement **Huffman's coding**-algorithm
  - [ ] Use `bitset` 
- [ ] Implement **range coding**-algorithm
- [ ] Implement **ANS**-algorithm
- [ ] Add choice of what FASTQ-file's part encode with what algorithm
- [ ] Collect all files 
  - [ ] Collect of all files to one directory
