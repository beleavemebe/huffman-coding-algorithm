# Huffman Coding Algorithm
An implementation of David Huffman's coding algorithm in C.
## Usage
Once the code is compiled, use the executable as such
```bash
# Encode a file
./huffman.exe --encode myfile encoded
# Decode a source file from the encoded one   
./huffman.exe --decode encoded decoded   
```
## Note
For any lurkers, this is a faulty implementation. 
The data structures are fine, but the actual encoding/decoding code 
was written in a state of extreme sleep deprivation to meet the 
deadline, and hence was spotted to not work on JPEG and MKV files, 
also causing corrupted sound for MP3 files.

Any interested people are encouraged to submit a PR with the fix. 