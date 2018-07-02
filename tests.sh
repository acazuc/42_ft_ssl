#!/bin/bash
test_hash_short()
{
	echo "$1 ft_ssl short"
	echo "plop" | ./ft_ssl $1 -r
	echo "plop" | openssl $1 -r
	echo "$1 openssl short"
}

test_hash_long()
{
	echo "$1 ft_ssl long"
	./ft_ssl $1 -r Makefile
	openssl $1 -r Makefile
	echo "$1 openssl long"
}

test_hash()
{
	test_hash_short $1
	echo
	test_hash_long $1
}

test_des_encrypt()
{
	echo "$1 encrypt ft_ssl"
	key="1122334455667788"
	iv="8877665544332211"
	./ft_ssl $1 -e -k $key -v $iv -i Makefile | openssl sha512 -r
	openssl $1 -e -K $key -iv $iv -in Makefile | openssl sha512 -r
	echo "$1 encrypt openssl"
}

test_des_decrypt()
{
	echo "$1 decrypt ft_ssl"
	key="1122334455667788"
	iv="8877665544332211"
	file=`mktemp`
	cat Makefile | openssl $1 -a -e -K $key -iv $iv > $file
	./ft_ssl $1 -a -d -k $key -v $iv -i $file | openssl sha512 -r
	openssl $1 -a -d -K $key -iv $iv -in $file | openssl sha512 -r
	rm $file
	echo "$1 decrypt openssl"
}

test_des()
{
	test_des_encrypt $1
	echo
	test_des_decrypt $1
}

test_hash "md5"
echo
echo
test_hash "sha1"
echo
echo
test_hash "sha224"
echo
echo
test_hash "sha256"
echo
echo
test_hash "sha384"
echo
echo
test_hash "sha512"
echo
echo

echo "base64_encode ft_ssl short"
echo "plop" | ./ft_ssl base64 | openssl sha512 -r
echo "plop" | openssl base64 | openssl sha512 -r
echo "base64_encode openssl short"

echo

echo "base64_encode ft_ssl long"
cat Makefile | ./ft_ssl base64 | openssl sha512 -r
cat Makefile | openssl base64 | openssl sha512 -r
echo "base64_encode openssl long"

echo
echo

echo "base64_decode ft_ssl short"
echo "plop" | openssl base64 > tmp
./ft_ssl base64 -d -i tmp | openssl sha512 -r
base64 -d tmp | openssl sha512 -r
rm tmp
echo "base64_decode openssl short"

echo

echo "base64_decode ft_ssl long"
cat Makefile | openssl base64 > tmp
./ft_ssl base64 -d -i tmp | openssl sha512 -r
base64 -d tmp | openssl sha512 -r
rm tmp
echo "base64_decode openssl long"

echo
echo
test_des "des-ecb"
echo
echo
test_des "des-cbc"
echo
echo
test_des "des-pcbc"
echo
echo
test_des "des-cfb"
echo
echo
test_des "des-ofb"
