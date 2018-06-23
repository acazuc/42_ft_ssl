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
