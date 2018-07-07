#!/bin/bash -f
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

test_hash_all()
{
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

test_base64_all()
{
	test_base64
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

test_des_all()
{
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
}

test_bignum()
{
	ret_ftssl=`./ft_ssl bignum $2 $3 $4`
	print_result "$1" $ret_ftssl $5
}

test_bignum_all()
{
	test_bignum "add_simple" 1 + 2 3
	test_bignum "add_zero" 0 + 0 0
	test_bignum "add_one_zero" 1 + 0 1
	test_bignum "add_big_small" 112233445566778899 + 10 112233445566778909
	test_bignum "add_big_big" 112233445566778899 + 112233445566778899 224466891133557798
	test_bignum "add_huge_huge" 2538687043280516217968757858774735713134894094727501826178087490310416 + 1269343521640258108984378929387367856567447047363750913089043745155208 3808030564920774326953136788162103569702341142091252739267131235465624
	echo
	test_bignum "sub_simple" 3 - 2 1
	test_bignum "sub_zero" 0 - 0 0
	test_bignum "sub_one_zero" 1 - 0 1
	test_bignum "sub_big_small" 112233445566778899 - 10 112233445566778889
	test_bignum "sub_big_big" 112233445566778899 - 112233445566778889 10
	test_bignum "sub_huge_huge" 2538687043280516217968757858774735713134894094727501826178087490310416 - 1269343521640258108984378929387367856567447047363750913089043745155207 1269343521640258108984378929387367856567447047363750913089043745155209
	echo
	test_bignum "mul_simple" 3 '*' 2 6
	test_bignum "mul_zero" 3 '*' 0 0
	test_bignum "mul_one" 1 '*' 8 8
	test_bignum "mul_big_small" 112233445566778899 '*' 9 1010101010101010091
	test_bignum "mul_big_big" 112233445566778899 '*' 112233445566778899 12596346303791122097392430351652201
	test_bignum "mul_huge_huge" 2538687043280516217968757858774735713134894094727501826178087490310416 '*' 2538687043280516217968757858774735713134894094727501826178087490310316 6444931903720369624895988058295186490773351122708453192597035122359526207702594532528293432256556085010669425565620297661676703939007051456
	echo
	test_bignum "div_simple" 7 / 2 3
	test_bignum "div_zero" 7 / 0 ""
	test_bignum "div_one" 7 / 1 7
	test_bignum "div_big_small" 112233445566778899 / 9 12470382840753211
	test_bignum "div_big_big" 112233445566778899 / 112233445523 1000000
	test_bignum "div_huge_huge" 2538687043280516217968757858774735713134894094727501826178087490310416 / 25386870432805162179687578587747357546543 99999999999999999999999999999
}

all="hash base64 des bignum"

ops=${@:-$all}

for var in $ops
do
	case $var in
		"hash")
			test_hash_all
			echo
			;;
		"base64")
			test_base64_all
			echo
			;;
		"des")
			test_des_all
			echo
			;;
		"bignum")
			test_bignum_all
			echo
			;;
	esac
done
