#!/bin/bash
echo "md5 ft_ssl short"
echo "plop" | ./ft_ssl md5
echo "plop" | openssl md5 -r
echo "md5 openssl short"

echo

echo "md5 ft_ssl long"
cat Makefile | ./ft_ssl md5
cat Makefile | openssl md5 -r
echo "md5 openssl long"

echo
echo

echo "sha1 ft_ssl short"
echo "plop" | ./ft_ssl sha1
echo "plop" | openssl sha1 -r
echo "sha1 openssl short"

echo

echo "sha1 ft_ssl long"
cat Makefile | ./ft_ssl sha1
cat Makefile | openssl sha1 -r
echo "sha1 openssl long"

echo
echo

echo "sha224 ft_ssl short"
echo "plop" | ./ft_ssl sha224
echo "plop" | openssl sha224 -r
echo "sha224 openssl short"

echo

echo "sha224 ft_ssl long"
cat Makefile | ./ft_ssl sha224
cat Makefile | openssl sha224 -r
echo "sha224 openssl long"

echo
echo

echo "sha256 ft_ssl short"
echo "plop" | ./ft_ssl sha256
echo "plop" | openssl sha256 -r
echo "sha256 openssl short"

echo

echo "sha256 ft_ssl long"
cat Makefile | ./ft_ssl sha256
cat Makefile | openssl sha256 -r
echo "sha256 openssl long"

echo
echo

echo "sha384 ft_ssl short"
echo "plop" | ./ft_ssl sha384
echo "plop" | openssl sha384 -r
echo "sha384 openssl short"

echo

echo "sha384 ft_ssl long"
cat Makefile | ./ft_ssl sha384
cat Makefile | openssl sha384 -r
echo "sha384 openssl long"

echo
echo

echo "sha512 ft_ssl short"
echo "plop" | ./ft_ssl sha512
echo "plop" | openssl sha512 -r
echo "sha512 openssl short"

echo

echo "sha512 ft_ssl long"
cat Makefile | ./ft_ssl sha512
cat Makefile | openssl sha512 -r
echo "sha512 openssl long"

echo
echo

echo "base64_encode ft_ssl short"
echo "plop" | ./ft_ssl base64 | openssl sha512
echo "plop" | openssl base64 | openssl sha512
echo "base64_encode openssl short"

echo

echo "base64_encode ft_ssl long"
cat Makefile | ./ft_ssl base64 | openssl sha512
cat Makefile | openssl base64 | openssl sha512
echo "base64_encode openssl long"

echo
echo

echo "base64_decode ft_ssl short"
echo "plop" | openssl base64 > tmp
./ft_ssl base64 -d -i tmp | openssl sha512
base64 -d tmp | openssl sha512
rm tmp
echo "base64_decode openssl short"

echo

echo "base64_decode ft_ssl long"
cat Makefile | openssl base64 > tmp
./ft_ssl base64 -d -i tmp > b | openssl sha512
base64 -d tmp > a | openssl sha512
rm tmp
echo "base64_decode openssl long"
