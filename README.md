# mgiver
Simple archiver. It using Huffman's algorithm to encode/decode files.

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

**NB**: result `fq` file prints to the stdout.

## Parameters

- `-i` - input `fq`-file in encode / `arch`-folder in decode 
0 `-o` - `arch`-folder
- `-v` - verbose;
- `-e` - encode `fq`-file
- `-d` - decode `arch`-folder

# TODO

- [x] Implement **Huffman's coding**-algorithm
  - [ ] Use `bitset` 
- [ ] Implement **range coding**-algorithm
- [ ] Implement **ANS**-algorithm
- [ ] Add choice of what FASTQ-file's part encode with what algorithm
- [ ] Collect all files 
  - [x] Collect of all files to one directory
