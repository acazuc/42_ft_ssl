#!/bin/bash
print_result()
{
	echo -n "$1: "
	if [ "$2" == "$3" ]
	then
		echo -ne "\e[1;32mPassed"
	else
		echo -ne "\e[1;31mNot passed"
	fi
	echo -e "\e[0;0m"
}

test_hash_do()
{
	ret_ftssl=`./ft_ssl $1 -r $2 | cut -d ' ' -f 1`
	ret_opssl=`openssl $1 -r $2  | cut -d ' ' -f 1`
	print_result "$1 $2" $ret_ftssl $ret_opssl
}

test_hash()
{
	test_hash_do $1 author
	test_hash_do $1 Makefile
}

test_base64_encode()
{
	ret_ftssl=`echo "plop" | ./ft_ssl base64 | openssl sha512 -r | cut -d ' ' -f 1`
	ret_opssl=`echo "plop" | openssl base64 | openssl sha512 -r | cut -d ' ' -f 1`
	print_result "base64 encode $1" $ret_ftssl $ret_opssl
}

test_base64_decode()
{
	file=`mktemp`
	cat $1 | openssl base64 > $file
	ret_ftssl=`./ft_ssl base64 -d -i $file | openssl sha512 -r | cut -d ' ' -f 1`
	ret_opssl=`openssl base64 -d -in $file | openssl sha512 -r | cut -d ' ' -f 1`
	rm $file
	print_result "base64 decode $1" $ret_ftssl $ret_opssl
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
	key="1122334455667788"
	iv="8877665544332211"
	ret_ftssl=`./ft_ssl $1 -e -k $key -v $iv -i $2 2>&- | openssl sha512 -r | cut -d ' ' -f 1`
	ret_opssl=`openssl $1 -e -K $key -iv $iv -in $2 2>&- | openssl sha512 -r | cut -d ' ' -f 1`
	print_result "$1 encrypt $2" $ret_ftssl $ret_opssl
}

test_des_decrypt()
{
	key="1122334455667788"
	iv="8877665544332211"
	file=`mktemp`
	cat $2 | openssl $1 -e -K $key -iv $iv > $file 2>&-
	ret_ftssl=`./ft_ssl $1 -d -k $key -v $iv -i $file 2>&- | openssl sha512 -r | cut -d ' ' -f 1`
	ret_opssl=`openssl $1 -d -K $key -iv $iv -in $file 2>&- | openssl sha512 -r | cut -d ' ' -f 1`
	rm $file
	print_result "$1 decrypt $2" $ret_ftssl $ret_opssl
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
