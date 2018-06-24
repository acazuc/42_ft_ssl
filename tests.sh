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
echo "plop" | openssl base64 | ./ft_ssl base64 -d | openssl sha512
echo "plop" | openssl base64 | openssl base64 -d | openssl sha512
echo "base64_decode openssl short"

echo

echo "base6_decode ft_ssl long"
cat Makefile | openssl base64 | ./ft_ssl base64 -d | openssl sha512
cat Makefile | openssl base64 | openssl base64 -d | openssl sha512
echo "base64_decode openssl long"
