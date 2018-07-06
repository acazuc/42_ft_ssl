#!/bin/bash
print_result()
{
	echo -n "$1: "
	if [ "$2" == "$3" ]
	then
		echo -ne "\e[1;32mPassed"
	else
		echo -ne "\e[1;31mFailed"
	fi
	echo -e "\e[0;0m"
}

test_hash_do()
{
	ret_ftssl=`./ft_ssl $1 -r $2 | cut -d ' ' -f 1 | openssl sha512 -r | cut -d ' ' -f 1`
	ret_opssl=`openssl $1 -r $2  | cut -d ' ' -f 1 | openssl sha512 -r | cut -d ' ' -f 1`
	print_result "$1 $2" $ret_ftssl $ret_opssl
}

test_hash()
{
	test_hash_do $1 author
	test_hash_do $1 Makefile
	test_hash_do $1 ft_ssl
	test_hash_do $1 /dev/null
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
	test_base64_encode ft_ssl
	test_base64_encode /dev/null
	test_base64_decode author
	test_base64_decode Makefile
	test_base64_decode ft_ssl
	test_base64_decode /dev/null
}

test_des_encrypt()
{
	iv="8877665544332211"
	#./ft_ssl $1 -a -e -k $2 -v $iv -i $3 | hexdump
	#openssl $1 -a -e -K $2 -iv $iv -in $3 | hexdump
	ret_ftssl=`./ft_ssl $1 -a -e -k $2 -v $iv -i $3 2>&- | openssl sha512 -r | cut -d ' ' -f 1`
	ret_opssl=`openssl $1 -a -e -K $2 -iv $iv -in $3 2>&- | openssl sha512 -r | cut -d ' ' -f 1`
	print_result "$1 encrypt $3" $ret_ftssl $ret_opssl
}

test_des_decrypt()
{
	iv="8877665544332211"
	file=`mktemp`
	cat $3 | openssl $1 -e -K $2 -iv $iv > $file 2>&-
	#./ft_ssl $1 -d -k $2 -v $iv -i $file | hexdump
	#openssl $1 -d -K $2 -iv $iv -in $file | hexdump
	ret_ftssl=`./ft_ssl $1 -d -k $2 -v $iv -i $file 2>&- | openssl sha512 -r | cut -d ' ' -f 1`
	ret_opssl=`openssl $1 -d -K $2 -iv $iv -in $file 2>&- | openssl sha512 -r | cut -d ' ' -f 1`
	rm $file
	print_result "$1 decrypt $3" $ret_ftssl $ret_opssl
}

test_des()
{
	test_des_encrypt $1 $2 author
	test_des_encrypt $1 $2 Makefile
	test_des_encrypt $1 $2 ft_ssl
	test_des_encrypt $1 $2 /dev/null
	test_des_decrypt $1 $2 author
	test_des_decrypt $1 $2 Makefile
	test_des_decrypt $1 $2 ft_ssl
	test_des_decrypt $1 $2 /dev/null
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

des_key_1="0123456789abcdef"
des_key_2="0123456789abcdef1122334455667788"
des_key_3="0123456789abcdef1122334455667788fedcba9876543210"

test_des "des-ecb" $des_key_1
echo
test_des "des-cbc" $des_key_1
echo
test_des "des-pcbc" $des_key_1
echo
test_des "des-cfb" $des_key_1
echo
test_des "des-ofb" $des_key_1
echo
test_des "des-ede-ecb" $des_key_2
echo
test_des "des-ede-cbc" $des_key_2
echo
test_des "des-ede-pcbc" $des_key_2
echo
test_des "des-ede-cfb" $des_key_2
echo
test_des "des-ede-ofb" $des_key_2
echo
test_des "des-ede3-ecb" $des_key_3
echo
test_des "des-ede3-cbc" $des_key_3
echo
test_des "des-ede3-pcbc" $des_key_3
echo
test_des "des-ede3-cfb" $des_key_3
echo
test_des "des-ede3-ofb" $des_key_3
