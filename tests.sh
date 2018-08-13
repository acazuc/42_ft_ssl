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
	#./ft_ssl $1 -r $2
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
	test_hash md4
	echo
	test_hash md5
	echo
	test_hash sha1
	echo
	test_hash sha224
	echo
	test_hash sha256
	echo
	test_hash sha384
	echo
	test_hash sha512
}

test_base64_encode()
{
	ret_ftssl=`./ft_ssl base64 -i $1 | openssl sha512 -r | cut -d ' ' -f 1`
	ret_opssl=`openssl base64 -in $1 | openssl sha512 -r | cut -d ' ' -f 1`
	print_result "base64 encode $1" $ret_ftssl $ret_opssl
}

test_base64_decode()
{
	file=`mktemp`
	cat $1 | openssl base64 > $file
	#./ft_ssl base64 -d -i $file | hexdump -C
	#openssl base64 -d -in $file | hexdump -C
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

test_cipher_encrypt()
{
	iv="8877665544332211"
	#./ft_ssl $1 -e -k $2 -v $iv -i $3 | hexdump -C
	#openssl $1 -e -K $2 -iv $iv -in $3 | hexdump -C
	ret_ftssl=`./ft_ssl $1 -a -e -k $2 -v $iv -i $3 2>&- | openssl sha512 -r | cut -d ' ' -f 1`
	ret_opssl=`openssl $1 -a -e -K $2 -iv $iv -in $3 2>&- | openssl sha512 -r | cut -d ' ' -f 1`
	print_result "$1 encrypt $3" $ret_ftssl $ret_opssl
}

test_cipher_decrypt()
{
	iv="8877665544332211"
	file=`mktemp`
	cat $3 | openssl $1 -a -e -K $2 -iv $iv > $file 2>&-
	#./ft_ssl $1 -a -d -k $2 -v $iv -i $file | hexdump -C
	#openssl $1 -a -d -K $2 -iv $iv -in $file | hexdump -C
	ret_ftssl=`./ft_ssl $1 -a -d -k $2 -v $iv -i $file 2>&- | openssl sha512 -r | cut -d ' ' -f 1`
	ret_opssl=`openssl $1 -a -d -K $2 -iv $iv -in $file 2>&- | openssl sha512 -r | cut -d ' ' -f 1`
	rm $file
	print_result "$1 decrypt $3" $ret_ftssl $ret_opssl
}

test_cipher()
{
	test_cipher_encrypt $1 $2 author
	test_cipher_encrypt $1 $2 Makefile
	test_cipher_encrypt $1 $2 ft_ssl
	test_cipher_encrypt $1 $2 /dev/null
	test_cipher_decrypt $1 $2 author
	test_cipher_decrypt $1 $2 Makefile
	test_cipher_decrypt $1 $2 ft_ssl
	test_cipher_decrypt $1 $2 /dev/null
}

test_des_part()
{
	test_cipher $1-ecb $2
	echo
	test_cipher $1-cbc $2
	echo
	test_cipher $1-pcbc $2
	echo
	test_cipher $1-cfb $2
	echo
	test_cipher $1-ofb $2
}

test_des1()
{
	key="0123456789abcdef"
	test_des_part des $key
}

test_des2()
{
	key="0123456789abcdef1122334455667788"
	test_des_part des-ede $key
}

test_des3()
{
	key="0123456789abcdef1122334455667788fedcba9876543210"
	test_des_part des-ede3 $key
}

test_des()
{
	test_des1
	echo
	test_des2
	echo
	test_des3
}

test_aes_part()
{
	test_cipher $1-ecb $2
	echo
	test_cipher $1-cbc $2
	echo
	test_cipher $1-pcbc $2
	echo
	test_cipher $1-cfb $2
	echo
	test_cipher $1-ofb $2
}

test_aes128()
{
	key="0123456789abcdef1122334455667788"
	test_aes_part aes-128 $key
}

test_aes192()
{
	key="0123456789abcdef1122334455667788fedcba9876543210"
	test_aes_part aes-192 $key
}

test_aes256()
{
	key="0123456789abcdef1122334455667788fedcba98765432108877665544332211"
	test_aes_part aes-256 $key
}

test_aes()
{
	test_aes128
	echo
	test_aes192
	echo
	test_aes256
}

test_camellia_part()
{
	test_cipher $1-ecb $2
	echo
	test_cipher $1-cbc $2
	echo
	test_cipher $1-pcbc $2
	echo
	test_cipher $1-cfb $2
	echo
	test_cipher $1-ofb $2
}

test_camellia128()
{
	key="0123456789abcdef1122334455667788"
	test_camellia_part camellia-128 $key
}

test_camellia192()
{
	key="0123456789abcdef1122334455667788fedcba9876543210"
	test_camellia_part camellia-192 $key
}

test_camellia256()
{
	key="0123456789abcdef1122334455667788fedcba98765432108877665544332211"
	test_camellia_part camellia-256 $key
}

test_camellia()
{
	test_camellia128
	echo
	test_camellia192
	echo
	test_camellia256
}

test_chacha20()
{
	key="0123456789abcdef1122334455667788fedcba98765432108877665544332211"
	test_cipher chacha20 $key
}

test_rc4()
{
	key="0123456789abcdef1122334455667788"
	test_cipher rc4 $key
}

test_bignum()
{
	ret_ftssl=`./ft_ssl bignum $2 $3 $4`
	print_result $1 $ret_ftssl $5
}

test_bignum_all()
{
	test_bignum add_simple 1 + 2 3
	test_bignum add_zero 0 + 0 0
	test_bignum add_one_zero 1 + 0 1
	test_bignum add_big_small 112233445566778899 + 10 112233445566778909
	test_bignum add_big_big 112233445566778899 + 112233445566778899 224466891133557798
	test_bignum add_huge_huge 2538687043280516217968757858774735713134894094727501826178087490310416 + 1269343521640258108984378929387367856567447047363750913089043745155208 3808030564920774326953136788162103569702341142091252739267131235465624
	echo
	test_bignum add_negative_png 5 + -2 3
	test_bignum add_negative_pnl 2 + -5 -3
	test_bignum add_negative_npg -6 + 4 -2
	test_bignum add_negative_npl -5 + 9 4
	test_bignum add_negative_nng -5 + -4 -9
	test_bignum add_negative_nnl -3 + -9 -12
	echo
	test_bignum sub_simple 3 - 2 1
	test_bignum sub_zero 0 - 0 0
	test_bignum sub_one_zero 1 - 0 1
	test_bignum sub_big_small 112233445566778899 - 10 112233445566778889
	test_bignum sub_big_big 112233445566778899 - 112233445566778889 10
	test_bignum sub_huge_huge 2538687043280516217968757858774735713134894094727501826178087490310416 - 1269343521640258108984378929387367856567447047363750913089043745155207 1269343521640258108984378929387367856567447047363750913089043745155209
	echo
	test_bignum sub_negative_png 5 - -2 7
	test_bignum sub_negative_pnl 3 - -7 10
	test_bignum sub_negative_npg -7 - 4 -11
	test_bignum sub_negative_npl -2 - 5 -7
	test_bignum sub_negative_nng -9 - -3 -6
	test_bignum sub_negative_nnl -4 - -9 5
	echo
	test_bignum mul_simple 3 '*' 2 6
	test_bignum mul_zero 3 '*' 0 0
	test_bignum mul_one 1 '*' 8 8
	test_bignum mul_big_small 112233445566778899 '*' 9 1010101010101010091
	test_bignum mul_big_big 112233445566778899 '*' 112233445566778899 12596346303791122097392430351652201
	test_bignum mul_huge_huge 2538687043280516217968757858774735713134894094727501826178087490310416 '*' 2538687043280516217968757858774735713134894094727501826178087490310316 6444931903720369624895988058295186490773351122708453192597035122359526207702594532528293432256556085010669425565620297661676703939007051456
	echo
	test_bignum mul_negative_pn 6 '*' -2 -12
	test_bignum mul_negative_np -3 '*' 7 -21
	test_bignum mul_negative_nn -5 '*' -3 15
	echo
	test_bignum div_simple 7 / 2 3
	test_bignum div_zero 7 / 0 ""
	test_bignum div_one 7 / 1 7
	test_bignum div_big_small 112233445566778899 / 9 12470382840753211
	test_bignum div_big_big 112233445566778899 / 112233445523 1000000
	test_bignum div_huge_huge 2538687043280516217968757858774735713134894094727501826178087490310416 / 25386870432805162179687578587747357546543 99999999999999999999999999999
	echo
	test_bignum div_negative_pn -7 / 3 -2
	test_bignum div_negative_np 13 / -3 -4
	test_bignum div_negative_nn -15 / -4 3
	echo
	test_bignum mod_simple 7 % 2 1
	test_bignum mod_zero 7 % 0 ""
	test_bignum mod_one 7 % 1 0
	test_bignum mod_big_small 112233445566778899 % 15 9
	test_bignum mod_big_big 112233445566778899 % 112233445523 43778899
	test_bignum mod_huge_huge 2538687043280516217968757858774735713134894094727501826178087490310416 % 25386870432805162179687578587747357546543 25386828913399256907189404765834847856959
	echo
	test_bignum mod_negative_pn1 12 % -4 -0
	test_bignum mod_negative_pn2 13 % -4 -3
	test_bignum mod_negative_pn3 14 % -4 -2
	test_bignum mod_negative_pn4 15 % -4 -1
	test_bignum mod_negative_pn5 16 % -4 -0
	test_bignum mod_negative_np1 -8 % 3 1
	test_bignum mod_negative_np2 -9 % 3 0
	test_bignum mod_negative_np3 -10 % 3 2
	test_bignum mod_negative_np4 -11 % 3 1
	test_bignum mod_negative_nn1 -14 % -3 -2
	test_bignum mod_negative_nn2 -15 % -3 -0
	test_bignum mod_negative_nn3 -16 % -3 -1
	test_bignum mod_negative_nn4 -17 % -3 -2
	echo
	test_bignum exp_simple 7 ^ 2 49
	test_bignum exp_zero 7 ^ 0 1
	test_bignum exp_one 7 ^ 1 7
	test_bignum exp_big_small 112233445566778899 ^ 15 5647216521307535910774570193454558148429904499572797187291697998843222979973212935737405421983603075035348202218480219580465507643671377868824511584887435285792703089192748536777340314991591476660891321860983157324859273472811684181253631127619682449633499
	test_bignum exp_huge_small 2538687043280516217968757858774735713134894094727501826178087490310416 ^ 5 105449817522143713873289191736816315467970330682548964008145209069279544391796791572803429807023304312766876266272581399518725843020156573640514089230038703743453303966007461476603345363277518865734459405413382165767490114833793451131084417922288730672653166013004415494808153304408837782464780024258853874874741165611254153116498208168945386520576
	echo
	test_bignum exp_negative_even -14 ^ 6 7529536
	test_bignum exp_negative_odd -13 ^ 5 -371293
	echo
	test_bignum lshift_simple 7 "<<" 2 28
	test_bignum lshift_zero 7 "<<" 0 7
	test_bignum lshift_one 7 "<<" 1 14
	test_bignum lshift_big_small 112233445566778899 "<<" 13 919416386083052740608
	test_bignum lshift_huge_small 2538687043280516217968757858774735713134894094727501826178087490310416 "<<" 13 20796924258553988857600064379082634962001052424007694960050892720622927872
	echo
	test_bignum lshift_negative -23 "<<" 4 -368
	echo
	test_bignum rshift_simple 7 ">>" 2 1
	test_bignum rshift_zero 7 ">>" 0 7
	test_bignum rshift_one 7 ">>" 1 3
	test_bignum rshift_big_small 112233445566778899 ">>" 13 13700371773288
	test_bignum rshift_huge_small 2538687043280516217968757858774735713134894094727501826178087490310416 ">>" 13 309898320712953639888764387057462855607286876797790750265879820594
	echo
	test_bignum rshift_negative -43 ">>" 3 -5
	echo
	test_bignum lshift1_small 7 "<<1" osef 14
	test_bignum lshift1_big 112233445566778899 "<<1" osef 224466891133557798
	test_bignum lshift1_huge 2538687043280516217968757858774735713134894094727501826178087490310416 "<<1" osef 5077374086561032435937515717549471426269788189455003652356174980620832
	echo
	test_bignum lshift1_negative -33 "<<1" osef -66
	echo
	test_bignum rshift1_small 7 ">>1" osef 3
	test_bignum rshift1_big 112233445566778899 ">>1" osef 56116722783389449
	test_bignum rshift1_huge 2538687043280516217968757858774735713134894094727501826178087490310416 ">>1" osef 1269343521640258108984378929387367856567447047363750913089043745155208
	echo
	test_bignum rshift1_negative -54 ">>1" "osef" -27
	echo
	test_bignum is_prime_small_yes 7 is_prime osef 1
	test_bignum is_prime_small_no 8 is_prime osef 0
	test_bignum is_prime_big_yes 32416189853 is_prime osef 1
	test_bignum is_prime_big_no 32416189793 is_prime osef 0
	test_bignum is_prime_huge_yes 170141183460469231731687303715884105727 is_prime osef 1
	test_bignum is_prime_huge_no 170141183460469231731647303715884105727 is_prime osef 0
	test_bignum is_prime_huge_yes 14693679385278593849609206715278070972733319459651094018859396328480215743184089660644531 is_prime osef 1
	test_bignum is_prime_huge_no 14693679385278593849609106715278070972733319459651094018859396328480215743184089660644531 is_prime osef 0
	test_bignum is_prime_huge_yes 43570062353753446053455610056679740005056966111842089407838902783209959981593077811330507328327968191581 is_prime osef 1
	test_bignum is_prime_huge_no 43570062353753446053455610056679740005056966111842089407838902783209959981593077812330507328327968191581 is_prime osef 0
	test_bignum is_prime_huge_yes 173595967255825177671338937551019479316666998993775123240829393474377123659353963383337070902624048512825454641905090447123113341790233547359778733674889927077625565221007272383568497900935065546549429354535026002846488966213929642837090828644809149794625119581137692313935281347548744981442897801650653080519 is_prime osef 1
	test_bignum is_prime_huge_no 173595967255825177671338937551019479316666998993775123240829393474377123659353963373337070902624048512825454641905090447123113341790233547359778733674889927077625565221007272383568497900935065546549429354535026002846488966213929642837090828644809149794625119581137692313935281347548744981442897801650653080519 is_prime osef 0
}

ops=${@:-"hash base64 des aes camellia chacha20 rc4 bignum"}

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
			test_des
			echo
			;;
		"des1")
			test_des1
			echo
			;;
		"des2")
			test_des2
			echo
			;;
		"des3")
			test_des3
			echo
			;;
		"aes")
			test_aes
			echo
			;;
		"aes-128")
			test_aes128
			echo
			;;
		"aes-192")
			test_aes192
			echo
			;;
		"aes-256")
			test_aes256
			echo
			;;
		"camellia")
			test_camellia
			echo
			;;
		"camellia-128")
			test_camellia128
			echo
			;;
		"camellia-192")
			test_camellia192
			echo
			;;
		"camellia-256")
			test_camellia256
			echo
			;;
		"chacha20")
			test_chacha20
			echo
			;;
		"rc4")
			test_rc4
			echo
			;;
		"bignum")
			test_bignum_all
			echo
			;;
	esac
done
