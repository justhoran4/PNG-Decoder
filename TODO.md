# TODO

## Parser Overview

- [ ] Decode PNG integer fields independently of host byte order. PNG stores multi-byte integers in big-endian order; avoid relying on reversing bytes into native integer memory, which only works as intended on little-endian hosts.
- [ ] Check chunk lengths against the remaining input before reading or allocating chunk data.
- [ ] Handle allocation failures and ensure chunk data and parser nodes are released on all paths.
- [ ] Define behavior for unknown chunk types, including safely skipping them when permitted.
- [ ] Track chunk ordering and required chunk presence.
- [ ] Implement CRC calculation and comparison for each chunk.
- [ ] Separate parsing from diagnostic output; avoid unconditional `printf` calls in chunk decoders.
- [ ] Add tests for valid chunks, truncated input, boundary lengths, and representative field values.
- [ ] Document supported PNG features and unsupported cases.

## Critical Chunks

### IHDR

- [ ] Decode width and height using explicit big-endian conversion.
- [ ] Parse all seven IHDR fields: width, height, bit depth, color type, compression method, filter method, and interlace method.
- [ ] Ensure the decoder receives enough payload bytes before accessing the 13-byte IHDR data.
- [ ] Add tests confirming each field is read from the correct byte offset.

### PLTE

- [ ] Parse palette entries as RGB triplets.
- [ ] Store the palette in a representation that supports the full allowed entry count.
- [ ] Handle the relationship between palette entries and indexed-color image data.

### IDAT

- [ ] Collect image data across consecutive IDAT chunks.
- [ ] Decompress concatenated image data using the PNG compression method.
- [ ] Pass decompressed scanlines to the PNG filter reconstruction stage.

### IEND

- [ ] Parse the end marker and stop chunk processing.
- [ ] Handle trailing bytes after IEND according to the parser's chosen policy.

## Ancillary Chunks

### cHRM

- [ ] Parse the eight 32-bit chromaticity values using big-endian conversion.

### gAMA

- [ ] Parse the 32-bit gamma value using big-endian conversion.

### iCCP

- [ ] Parse the profile name, null separator, compression method, and compressed profile data.
- [ ] Handle variable-length profile data without fixed-size assumptions.

### sBIT

- [ ] Parse significant-bit fields according to the image color type.

### sRGB

- [ ] Parse the rendering-intent byte.

### bKGD

- [ ] Parse the background value according to the image color type and palette availability.

### hIST

- [ ] Parse the per-palette-entry histogram values.
- [ ] Use the palette size to determine the number of histogram entries.

### tRNS

- [ ] Parse transparency data according to the image color type.
- [ ] Support palette alpha values and grayscale or truecolor transparent samples.

### pHYs

- [ ] Parse the X and Y pixels-per-unit values using big-endian conversion.
- [ ] Parse the unit specifier.

### sPLT

- [ ] Parse the palette name, sample depth, and variable-length palette entries.
- [ ] Support both 8-bit and 16-bit sample depths.

### tIME

- [ ] Parse the year and date/time fields from the seven-byte payload.

### iTXt

- [ ] Parse the keyword, compression fields, language tag, translated keyword, and text.
- [ ] Handle null-separated and variable-length fields safely.
- [ ] Decompress the text when the compression flag requires it.

### tEXt

- [ ] Parse the keyword and text separated by a null byte.
- [ ] Handle variable-length text data.

### zTXt

- [ ] Parse the keyword, compression method, and compressed text.
- [ ] Decompress the text and handle variable-length data safely.
