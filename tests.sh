#!/bin/bash

FTSSL_BIN=./ft_ssl
OPSSL_BIN=openssl

print_result_ok()
{
	printf "\e[0m[\e[1;32mOK\e[0m] $1\e[0m\n"
}

print_result_ko()
{
	printf "\e[0m[\e[1;31mKO\e[0m] $1\e[0m\n"
}

print_result()
{
	if [ "$2" == "$3" ]
	then
		print_result_ok "$1"
	else
		print_result_ko "$1"
	fi
}

test_hash_do()
{
	ret_ftssl=`$FTSSL_BIN $1 $2 | cut -d ' ' -f3`
	ret_opssl=`$OPSSL_BIN $1 $2 | cut -d ' ' -f2`
	print_result "$1 $2" $ret_ftssl $ret_opssl
}

test_hash()
{
	test_hash_do $1 author
	test_hash_do $1 Makefile
	test_hash_do $1 ft_ssl
	test_hash_do $1 /dev/null
}

test_hash_sha2_do()
{
	ret_ftssl=`$FTSSL_BIN sha$1 $2 | cut -d ' ' -f3`
	ret_opssl=`$OPSSL_BIN sha1 -sha$1 $2 | cut -d ' ' -f2`
	print_result "sha$1 $2" $ret_ftssl $ret_opssl
}

test_hash_sha2()
{
	test_hash_sha2_do $1 author
	test_hash_sha2_do $1 Makefile
	test_hash_sha2_do $1 ft_ssl
	test_hash_sha2_do $1 /dev/null
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
	ret_ftssl=`$FTSSL_BIN base64 -i $1  | $OPSSL_BIN sha1 | cut -d ' ' -f2`
	ret_opssl=`$OPSSL_BIN base64 -in $1 | $OPSSL_BIN sha1 | cut -d ' ' -f2`
	print_result "base64 encode $1" $ret_ftssl $ret_opssl
}

test_base64_decode()
{
	file=`mktemp`
	cat $1 | openssl base64 > $file
	ret_ftssl=`$FTSSL_BIN base64 -d -i $file  | $OPSSL_BIN sha1 | cut -d ' ' -f2`
	ret_opssl=`$OPSSL_BIN base64 -d -in $file | $OPSSL_BIN sha1 | cut -d ' ' -f2`
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
	ret_ftssl=`$FTSSL_BIN $1 -a -e -k $2 -v $iv -i $3 2>&-   | $OPSSL_BIN sha1 | cut -d ' ' -f2`
	ret_opssl=`$OPSSL_BIN $1 -a -e -K $2 -iv $iv -in $3 2>&- | $OPSSL_BIN sha1 | cut -d ' ' -f2`
	print_result "$1 encrypt $3" $ret_ftssl $ret_opssl
}

test_cipher_decrypt()
{
	iv="8877665544332211"
	file=`mktemp`
	cat $3 | openssl $1 -a -e -K $2 -iv $iv > $file 2>&-
	ret_ftssl=`$FTSSL_BIN $1 -a -d -k $2 -v $iv -i $file 2>&-   | $OPSSL_BIN sha1 | cut -d ' ' -f2`
	ret_opssl=`$OPSSL_BIN $1 -a -d -K $2 -iv $iv -in $file 2>&- | $OPSSL_BIN sha1 | cut -d ' ' -f2`
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
	ret_ftssl=`$FTSSL_BIN bignum $2 "$3" $4`
	print_result "bignum_$1" $ret_ftssl $5
}

test_bignum_all()
{
	test_bignum add_simple 1 + 2 3
	test_bignum add_zero 0 + 0 0
	test_bignum add_one_zero 1 + 0 1
	test_bignum add_big_small 112233445566778899 + 10 112233445566778909
	test_bignum add_big_big 112233445566778899 + 112233445566778899 224466891133557798
	test_bignum add_huge_huge 2538687043280516217968757858774735713134894094727501826178087490310416 + 1269343521640258108984378929387367856567447047363750913089043745155208 3808030564920774326953136788162103569702341142091252739267131235465624
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
	test_bignum sub_negative_png 5 - -2 7
	test_bignum sub_negative_pnl 3 - -7 10
	test_bignum sub_negative_npg -7 - 4 -11
	test_bignum sub_negative_npl -2 - 5 -7
	test_bignum sub_negative_nng -9 - -3 -6
	test_bignum sub_negative_nnl -4 - -9 5
	echo
	test_bignum mul_simple 3 _ 2 6
	test_bignum mul_zero 3 _ 0 0
	test_bignum mul_one 1 _ 8 8
	test_bignum mul_big_small 112233445566778899 _ 9 1010101010101010091
	test_bignum mul_big_big 112233445566778899 _ 112233445566778899 12596346303791122097392430351652201
	test_bignum mul_huge_huge 2538687043280516217968757858774735713134894094727501826178087490310416 _ 2538687043280516217968757858774735713134894094727501826178087490310316 6444931903720369624895988058295186490773351122708453192597035122359526207702594532528293432256556085010669425565620297661676703939007051456
	test_bignum mul_negative_pn 6 _ -2 -12
	test_bignum mul_negative_np -3 _ 7 -21
	test_bignum mul_negative_nn -5 _ -3 15
	echo
	test_bignum div_simple 7 / 2 3
	test_bignum div_zero 7 / 0 ""
	test_bignum div_one 7 / 1 7
	test_bignum div_big_small 112233445566778899 / 9 12470382840753211
	test_bignum div_big_big 112233445566778899 / 112233445523 1000000
	test_bignum div_huge_huge 2538687043280516217968757858774735713134894094727501826178087490310416 / 25386870432805162179687578587747357546543 99999999999999999999999999999
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
	test_bignum exp_negative_even -14 ^ 6 7529536
	test_bignum exp_negative_odd -13 ^ 5 -371293
	echo
	test_bignum lshift_simple 7 "<<" 2 28
	test_bignum lshift_zero 7 "<<" 0 7
	test_bignum lshift_one 7 "<<" 1 14
	test_bignum lshift_big_small 112233445566778899 "<<" 13 919416386083052740608
	test_bignum lshift_huge_small 2538687043280516217968757858774735713134894094727501826178087490310416 "<<" 13 20796924258553988857600064379082634962001052424007694960050892720622927872
	test_bignum lshift_negative -23 "<<" 4 -368
	echo
	test_bignum rshift_simple 7 ">>" 2 1
	test_bignum rshift_zero 7 ">>" 0 7
	test_bignum rshift_one 7 ">>" 1 3
	test_bignum rshift_big_small 112233445566778899 ">>" 13 13700371773288
	test_bignum rshift_huge_small 2538687043280516217968757858774735713134894094727501826178087490310416 ">>" 13 309898320712953639888764387057462855607286876797790750265879820594
	test_bignum rshift_negative -43 ">>" 3 -5
	echo
	test_bignum lshift1_small 7 "<<1" osef 14
	test_bignum lshift1_big 112233445566778899 "<<1" osef 224466891133557798
	test_bignum lshift1_huge 2538687043280516217968757858774735713134894094727501826178087490310416 "<<1" osef 5077374086561032435937515717549471426269788189455003652356174980620832
	test_bignum lshift1_negative -33 "<<1" osef -66
	echo
	test_bignum rshift1_small 7 ">>1" osef 3
	test_bignum rshift1_big 112233445566778899 ">>1" osef 56116722783389449
	test_bignum rshift1_huge 2538687043280516217968757858774735713134894094727501826178087490310416 ">>1" osef 1269343521640258108984378929387367856567447047363750913089043745155208
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

test_genrsa()
{
	$FTSSL_BIN genrsa 15 -out /tmp/ftssl_rsa_key 2> /dev/null && print_result_ko genrsa_tooshort || print_result_ok genrsa_tooshort
	$FTSSL_BIN genrsa 16 -out /tmp/ftssl_rsa_key 2> /dev/null && print_result_ok genrsa_simple || print_result_ko genrsa_simple
	$OPSSL_BIN rsa -check -in /tmp/ftssl_rsa_key -noout > /dev/null 2> /dev/null && print_result_ok genrsa_check || print_result_ko genrsa_check
}

test_rsautl()
{
	#generate key
	$FTSSL_BIN genrsa 256 -out /tmp/ftssl_rsa_key 2> /dev/null

	#encrypt with priv
	$FTSSL_BIN rsautl -encrypt -inkey /tmp/ftssl_rsa_key -in author -out /tmp/ftssl_author
	$OPSSL_BIN rsautl -decrypt -inkey /tmp/ftssl_rsa_key -in /tmp/ftssl_author -out /tmp/opssl_author
	df=`diff author /tmp/opssl_author`
	print_result rsautl_encrypt_priv $df ""

	#decrypt
	$OPSSL_BIN rsautl -encrypt -inkey /tmp/ftssl_rsa_key -in author -out /tmp/opssl_author
	$FTSSL_BIN rsautl -decrypt -inkey /tmp/ftssl_rsa_key -in /tmp/opssl_author -out /tmp/ftssl_author_2
	df=`diff /tmp/ftssl_author_2 author`
	print_result rsautl_decrypt $df ""

	#encrypt with public
	$OPSSL_BIN rsa -in /tmp/ftssl_rsa_key -out /tmp/opssl_rsa_key_pub -pubout > /dev/null 2> /dev/null
	$FTSSL_BIN rsautl -encrypt -pubin -inkey /tmp/opssl_rsa_key_pub -in author -out /tmp/ftssl_author_pub
	$OPSSL_BIN rsautl -decrypt -inkey /tmp/ftssl_rsa_key -in /tmp/ftssl_author_pub -out /tmp/opssl_author
	df=`diff author /tmp/opssl_author`
	print_result rsautl_encrypt_pub $df ""

	#decrypt with public
	$FTSSL_BIN rsautl -decrypt -pubin -inkey /tmp/opssl_rsa_key_pub -in /tmp/ft_ssl_author_pub > /dev/null 2> /dev/null && print_result_ko rsautl_decrypt_public || print_result_ok rsautl_decrypt_public

	#pubin with private key
	$FTSSL_BIN rsautl -encrypt -pubin -inkey /tmp/opssl_rsa_key -in author > /dev/null 2> /dev/null && print_result_ko rsautl_pubin_private || print_result_ok rsautl_pubin_private

	#no pubin with public key
	$FTSSL_BIN rsautl -encrypt -inkey /tmp/opssl_rsa_key_pub -in author > /dev/null 2> /dev/null && print_result_ko rsautl_nopubin_public || print_result_ok rsautl_nopubin_public

	#rsautl hexdump
	$OPSSL_BIN rsautl -encrypt -inkey /tmp/ftssl_rsa_key -in author -out /tmp/opssl_author
	$FTSSL_BIN rsautl -in /tmp/opssl_author -decrypt -inkey /tmp/ftssl_rsa_key -out /tmp/ftssl_hexdump_priv -hexdump
	$OPSSL_BIN rsautl -in /tmp/opssl_author -decrypt -inkey /tmp/ftssl_rsa_key -out /tmp/opssl_hexdump_priv -hexdump
	df=`diff /tmp/ftssl_hexdump_priv /tmp/opssl_hexdump_priv`
	print_result rsautl_hexdump $df ""

	#input too long
	$FTSSL_BIN rsautl -encrypt -inkey /tmp/ftssl_rsa_key -in Makefile -out /dev/null 2> /dev/null && print_result_ko rsautl_toolong || print_result_ok rsautl_toolong

	#rsa invalid pub
	$FTSSL_BIN rsautl -pubin -inkey /tmp/ftssl_rsa_key -in author > /dev/null 2> /dev/null && print_result_ko rsautl_invalid_pubin || print_result_ok rsa_invalid_pubin

	#rsa invalid priv
	$FTSSL_BIN rsautl -inkey /tmp/ftssl_rsa_key_pub -in author > /dev/null 2> /dev/null && print_result_ko rsautl_invalid_privin || print_result_ok rsa_invalid_privin
}

test_rsa()
{
	#generate key
	$FTSSL_BIN genrsa 256 -out /tmp/ftssl_rsa_key 1>&- 2>&-

	#rsa priv to priv
	$FTSSL_BIN rsa -in /tmp/ftssl_rsa_key -out /tmp/ftssl_rsa_key_priv
	$OPSSL_BIN rsa -in /tmp/ftssl_rsa_key -out /tmp/opssl_rsa_key_priv >&- 2>&-
	df=`diff /tmp/ftssl_rsa_key_priv /tmp/opssl_rsa_key_priv`
	print_result rsa_privtopriv $df ""

	#rsa priv to pub
	$FTSSL_BIN rsa -in /tmp/ftssl_rsa_key -out /tmp/ftssl_rsa_key_pub -pubout
	$OPSSL_BIN rsa -in /tmp/ftssl_rsa_key -out /tmp/opssl_rsa_key_pub -pubout >&- 2>&-
	df=`diff /tmp/ftssl_rsa_key_pub /tmp/opssl_rsa_key_pub`
	print_result rsa_privtopub $df ""

	#rsa pub to pub
	$FTSSL_BIN rsa -pubin -in /tmp/ftssl_rsa_key_pub -out /tmp/ftssl_rsa_key_pub_2 -pubout
	$OPSSL_BIN rsa -pubin -in /tmp/ftssl_rsa_key_pub -out /tmp/opssl_rsa_key_pub_2 -pubout >&- 2>&-
	df=`diff /tmp/ftssl_rsa_key_pub_2 /tmp/opssl_rsa_key_pub_2`
	print_result rsa_pubtopub $df ""

	#rsa pub to priv
	$FTSSL_BIN rsa -pubin -in /tmp/ftssl_rsa_key_pub -out /tmp/ftssl_rsa_key_pub_3
	$OPSSL_BIN rsa -pubin -in /tmp/ftssl_rsa_key_pub -out /tmp/opssl_rsa_key_pub_3 >&- 2>&-
	df=`diff /tmp/ftssl_rsa_key_pub_3 /tmp/opssl_rsa_key_pub_3`
	print_result rsa_pubtopriv $df ""

	#rsa invalid pub
	$FTSSL_BIN rsa -pubin -in /tmp/ftssl_rsa_key > /dev/null 2> /dev/null && print_result_ko rsa_invalid_pubin || print_result_ok rsa_invalid_pubin

	#rsa invalid priv
	$FTSSL_BIN rsa -in /tmp/ftssl_rsa_key_pub > /dev/null 2> /dev/null && print_result_ko rsa_invalid_privin || print_result_ok rsa_invalid_privin
}

has_printed_ln=0

function nl_if_not_first()
{
	if [[ "$has_printed_ln" == 0 ]]
	then
		has_printed_ln=1
	else
		printf "\n"
	fi
}

ops=${@:-"hash base64 des aes camellia chacha20 rc4 bignum genrsa rsautl rsa"}

for var in $ops
do
	case $var in
		"hash")
			nl_if_not_first
			test_hash_all
			;;
		"base64")
			nl_if_not_first
			test_base64_all
			;;
		"des")
			nl_if_not_first
			test_des
			;;
		"des1")
			nl_if_not_first
			test_des1
			;;
		"des2")
			nl_if_not_first
			test_des2
			;;
		"des3")
			nl_if_not_first
			test_des3
			;;
		"aes")
			nl_if_not_first
			test_aes
			;;
		"aes-128")
			nl_if_not_first
			test_aes128
			;;
		"aes-192")
			nl_if_not_first
			test_aes192
			;;
		"aes-256")
			nl_if_not_first
			test_aes256
			;;
		"camellia")
			nl_if_not_first
			test_camellia
			;;
		"camellia-128")
			nl_if_not_first
			test_camellia128
			;;
		"camellia-192")
			nl_if_not_first
			test_camellia192
			;;
		"camellia-256")
			nl_if_not_first
			test_camellia256
			;;
		"chacha20")
			nl_if_not_first
			test_chacha20
			;;
		"rc4")
			nl_if_not_first
			test_rc4
			;;
		"bignum")
			nl_if_not_first
			test_bignum_all
			;;
		"genrsa")
			nl_if_not_first
			test_genrsa
			;;
		"rsautl")
			nl_if_not_first
			test_rsautl
			;;
		"rsa")
			nl_if_not_first
			test_rsa
			;;
	esac
done
