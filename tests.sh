#!/bin/bash
test_hash_do()
{
	echo -n "$1 $2: "
	ret_ftssl=`./ft_ssl $1 -r $2 | cut -d ' ' -f 1`
	ret_opssl=`openssl $1 -r $2  | cut -d ' ' -f 1`
	if [ "$ret_ftssl" == "$ret_opssl" ]
	then
		echo -ne "\e[1;32mPassed"
	else
		echo -ne "\e[1;31mNot passed"
	fi
	echo -e "\e[0;0m"
}

test_hash()
{
	test_hash_do $1 author
	test_hash_do $1 Makefile
}

test_base64_encode()
{
	echo -n "base64 encode $1: "
	ret_ftssl=`echo "plop" | ./ft_ssl base64 | openssl sha512 -r | cut -d ' ' -f 1`
	ret_opssl=`echo "plop" | openssl base64 | openssl sha512 -r | cut -d ' ' -f 1`
	if [ "$ret_ftssl" == "$ret_opssl" ]
	then
		echo -ne "\e[1;32mPassed"
	else
		echo -ne "\e[1;31mNot passed"
	fi
	echo -e "\e[0;0m"
}

test_base64_decode()
{
	echo -n "base64 decode $1: "
	file=`mktemp`
	cat $1 | openssl base64 > $file
	ret_ftssl=`./ft_ssl base64 -d -i $file | openssl sha512 -r | cut -d ' ' -f 1`
	ret_opssl=`openssl base64 -d -in $file | openssl sha512 -r | cut -d ' ' -f 1`
	rm $file
	if [ "$ret_ftssl" == "$ret_opssl" ]
	then
		echo -ne "\e[1;32mPassed"
	else
		echo -ne "\e[1;31mNot passed"
	fi
	echo -e "\e[0;0m"
}

test_base64()
{
	test_base64_encode author
	test_base64_encode Makefile
	test_base64_decode author
	test_base64_decode Makefile
}

test_des_encrypt()
{
	echo -n "$1 encrypt $2: "
	key="1122334455667788"
	iv="8877665544332211"
	ret_ftssl=`./ft_ssl $1 -e -k $key -v $iv -i $2 2>&- | openssl sha512 -r | cut -d ' ' -f 1`
	ret_opssl=`openssl $1 -e -K $key -iv $iv -in $2 2>&- | openssl sha512 -r | cut -d ' ' -f 1`
	if [ "$ret_ftssl" == "$ret_opssl" ]
	then
		echo -ne "\e[1;32mPassed"
	else
		echo -ne "\e[1;31mNot passed"
	fi
	echo -e "\e[0;0m"
}

test_des_decrypt()
{
	echo -n "$1 decrypt $2: "
	key="1122334455667788"
	iv="8877665544332211"
	file=`mktemp`
	cat $2 | openssl $1 -e -K $key -iv $iv > $file 2>&-
	ret_ftssl=`./ft_ssl $1 -d -k $key -v $iv -i $file 2>&- | openssl sha512 -r | cut -d ' ' -f 1`
	ret_opssl=`openssl $1 -d -K $key -iv $iv -in $file 2>&- | openssl sha512 -r | cut -d ' ' -f 1`
	rm $file
	if [ "$ret_ftssl" == "$ret_opssl" ]
	then
		echo -ne "\e[1;32mPassed"
	else
		echo -ne "\e[1;31mNot passed"
	fi
	echo -e "\e[0;0m"
}

test_des()
{
	test_des_encrypt $1 author
	test_des_encrypt $1 Makefile
	test_des_decrypt $1 author
	test_des_decrypt $1 Makefile
}

test_hash "md5"
echo
test_hash "sha1"
echo
test_hash "sha224"
echo
test_hash "sha256"
echo
test_hash "sha384"
echo
test_hash "sha512"
echo

test_base64
echo

test_des "des-ecb"
echo
test_des "des-cbc"
echo
test_des "des-pcbc"
echo
test_des "des-cfb"
echo
test_des "des-ofb"
