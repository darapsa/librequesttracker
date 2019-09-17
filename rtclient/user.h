#ifndef RTCLIENT_USER_H
#define RTCLIENT_USER_H

#include <stdbool.h>

enum rt_lang {
	RT_LANG_NONE = 0
		, RT_LANG_ar
		, RT_LANG_eu
		, RT_LANG_nb
		, RT_LANG_bg
		, RT_LANG_ca
		, RT_LANG_zh_cn
		, RT_LANG_zh_tw
		, RT_LANG_hr
		, RT_LANG_cs
		, RT_LANG_da
		, RT_LANG_nl
		, RT_LANG_en
		, RT_LANG_en_gb
		, RT_LANG_et
		, RT_LANG_fi
		, RT_LANG_fr
		, RT_LANG_de
		, RT_LANG_el
		, RT_LANG_hu
		, RT_LANG_is
		, RT_LANG_id
		, RT_LANG_it
		, RT_LANG_ja
		, RT_LANG_lv
		, RT_LANG_lt
		, RT_LANG_nn
		, RT_LANG_fa
		, RT_LANG_pl
		, RT_LANG_pt
		, RT_LANG_pt_br
		, RT_LANG_pt_pt
		, RT_LANG_ro
		, RT_LANG_ru
		, RT_LANG_sr
		, RT_LANG_sk
		, RT_LANG_sl
		, RT_LANG_es
		, RT_LANG_sv
		, RT_LANG_tr
};

enum rt_timezone {
	RT_TIMEZONE_NONE = 0
		, RT_TIMEZONE_Africa_Abidjan
		, RT_TIMEZONE_Africa_Accra
		, RT_TIMEZONE_Africa_Algiers
		, RT_TIMEZONE_Africa_Bissau
		, RT_TIMEZONE_Africa_Cairo
		, RT_TIMEZONE_Africa_Casablanca
		, RT_TIMEZONE_Africa_Ceuta
		, RT_TIMEZONE_Africa_El_Aaiun
		, RT_TIMEZONE_Africa_Johannesburg
		, RT_TIMEZONE_Africa_Juba
		, RT_TIMEZONE_Africa_Khartoum
		, RT_TIMEZONE_Africa_Lagos
		, RT_TIMEZONE_Africa_Maputo
		, RT_TIMEZONE_Africa_Monrovia
		, RT_TIMEZONE_Africa_Nairobi
		, RT_TIMEZONE_Africa_Ndjamena
		, RT_TIMEZONE_Africa_Sao_Tome
		, RT_TIMEZONE_Africa_Tripoli
		, RT_TIMEZONE_Africa_Tunis
		, RT_TIMEZONE_Africa_Windhoek
		, RT_TIMEZONE_America_Adak
		, RT_TIMEZONE_America_Anchorage
		, RT_TIMEZONE_America_Araguaina
		, RT_TIMEZONE_America_Argentina_Buenos_Aires
		, RT_TIMEZONE_America_Argentina_Catamarca
		, RT_TIMEZONE_America_Argentina_Cordoba
		, RT_TIMEZONE_America_Argentina_Jujuy
		, RT_TIMEZONE_America_Argentina_La_Rioja
		, RT_TIMEZONE_America_Argentina_Mendoza
		, RT_TIMEZONE_America_Argentina_Rio_Gallegos
		, RT_TIMEZONE_America_Argentina_Salta
		, RT_TIMEZONE_America_Argentina_San_Juan
		, RT_TIMEZONE_America_Argentina_San_Luis
		, RT_TIMEZONE_America_Argentina_Tucuman
		, RT_TIMEZONE_America_Argentina_Ushuaia
		, RT_TIMEZONE_America_Asuncion
		, RT_TIMEZONE_America_Atikokan
		, RT_TIMEZONE_America_Bahia
		, RT_TIMEZONE_America_Bahia_Banderas
		, RT_TIMEZONE_America_Barbados
		, RT_TIMEZONE_America_Belem
		, RT_TIMEZONE_America_Belize
		, RT_TIMEZONE_America_Blanc_Sablon
		, RT_TIMEZONE_America_Boa_Vista
		, RT_TIMEZONE_America_Bogota
		, RT_TIMEZONE_America_Boise
		, RT_TIMEZONE_America_Cambridge_Bay
		, RT_TIMEZONE_America_Campo_Grande
		, RT_TIMEZONE_America_Cancun
		, RT_TIMEZONE_America_Caracas
		, RT_TIMEZONE_America_Cayenne
		, RT_TIMEZONE_America_Chicago
		, RT_TIMEZONE_America_Chihuahua
		, RT_TIMEZONE_America_Costa_Rica
		, RT_TIMEZONE_America_Creston
		, RT_TIMEZONE_America_Cuiaba
		, RT_TIMEZONE_America_Curacao
		, RT_TIMEZONE_America_Danmarkshavn
		, RT_TIMEZONE_America_Dawson
		, RT_TIMEZONE_America_Dawson_Creek
		, RT_TIMEZONE_America_Denver
		, RT_TIMEZONE_America_Detroit
		, RT_TIMEZONE_America_Edmonton
		, RT_TIMEZONE_America_Eirunepe
		, RT_TIMEZONE_America_El_Salvador
		, RT_TIMEZONE_America_Fort_Nelson
		, RT_TIMEZONE_America_Fortaleza
		, RT_TIMEZONE_America_Glace_Bay
		, RT_TIMEZONE_America_Godthab
		, RT_TIMEZONE_America_Goose_Bay
		, RT_TIMEZONE_America_Grand_Turk
		, RT_TIMEZONE_America_Guatemala
		, RT_TIMEZONE_America_Guayaquil
		, RT_TIMEZONE_America_Guyana
		, RT_TIMEZONE_America_Halifax
		, RT_TIMEZONE_America_Havana
		, RT_TIMEZONE_America_Hermosillo
		, RT_TIMEZONE_America_Indiana_Indianapolis
		, RT_TIMEZONE_America_Indiana_Knox
		, RT_TIMEZONE_America_Indiana_Marengo
		, RT_TIMEZONE_America_Indiana_Petersburg
		, RT_TIMEZONE_America_Indiana_Tell_City
		, RT_TIMEZONE_America_Indiana_Vevay
		, RT_TIMEZONE_America_Indiana_Vincennes
		, RT_TIMEZONE_America_Indiana_Winamac
		, RT_TIMEZONE_America_Inuvik
		, RT_TIMEZONE_America_Iqaluit
		, RT_TIMEZONE_America_Jamaica
		, RT_TIMEZONE_America_Juneau
		, RT_TIMEZONE_America_Kentucky_Louisville
		, RT_TIMEZONE_America_Kentucky_Monticello
		, RT_TIMEZONE_America_La_Paz
		, RT_TIMEZONE_America_Lima
		, RT_TIMEZONE_America_Los_Angeles
		, RT_TIMEZONE_America_Maceio
		, RT_TIMEZONE_America_Managua
		, RT_TIMEZONE_America_Manaus
		, RT_TIMEZONE_America_Martinique
		, RT_TIMEZONE_America_Matamoros
		, RT_TIMEZONE_America_Mazatlan
		, RT_TIMEZONE_America_Menominee
		, RT_TIMEZONE_America_Merida
		, RT_TIMEZONE_America_Metlakatla
		, RT_TIMEZONE_America_Mexico_City
		, RT_TIMEZONE_America_Miquelon
		, RT_TIMEZONE_America_Moncton
		, RT_TIMEZONE_America_Monterrey
		, RT_TIMEZONE_America_Montevideo
		, RT_TIMEZONE_America_Nassau
		, RT_TIMEZONE_America_New_York
		, RT_TIMEZONE_America_Nipigon
		, RT_TIMEZONE_America_Nome
		, RT_TIMEZONE_America_Noronha
		, RT_TIMEZONE_America_North_Dakota_Beulah
		, RT_TIMEZONE_America_North_Dakota_Center
		, RT_TIMEZONE_America_North_Dakota_New_Salem
		, RT_TIMEZONE_America_Ojinaga
		, RT_TIMEZONE_America_Panama
		, RT_TIMEZONE_America_Pangnirtung
		, RT_TIMEZONE_America_Paramaribo
		, RT_TIMEZONE_America_Phoenix
		, RT_TIMEZONE_America_Port_au_Prince
		, RT_TIMEZONE_America_Port_of_Spain
		, RT_TIMEZONE_America_Porto_Velho
		, RT_TIMEZONE_America_Puerto_Rico
		, RT_TIMEZONE_America_Punta_Arenas
		, RT_TIMEZONE_America_Rainy_River
		, RT_TIMEZONE_America_Rankin_Inlet
		, RT_TIMEZONE_America_Recife
		, RT_TIMEZONE_America_Regina
		, RT_TIMEZONE_America_Resolute
		, RT_TIMEZONE_America_Rio_Branco
		, RT_TIMEZONE_America_Santarem
		, RT_TIMEZONE_America_Santiago
		, RT_TIMEZONE_America_Santo_Domingo
		, RT_TIMEZONE_America_Sao_Paulo
		, RT_TIMEZONE_America_Scoresbysund
		, RT_TIMEZONE_America_Sitka
		, RT_TIMEZONE_America_St_Johns
		, RT_TIMEZONE_America_Swift_Current
		, RT_TIMEZONE_America_Tegucigalpa
		, RT_TIMEZONE_America_Thule
		, RT_TIMEZONE_America_Thunder_Bay
		, RT_TIMEZONE_America_Tijuana
		, RT_TIMEZONE_America_Toronto
		, RT_TIMEZONE_America_Vancouver
		, RT_TIMEZONE_America_Whitehorse
		, RT_TIMEZONE_America_Winnipeg
		, RT_TIMEZONE_America_Yakutat
		, RT_TIMEZONE_America_Yellowknife
		, RT_TIMEZONE_Antarctica_Casey
		, RT_TIMEZONE_Antarctica_Davis
		, RT_TIMEZONE_Antarctica_DumontDUrville
		, RT_TIMEZONE_Antarctica_Macquarie
		, RT_TIMEZONE_Antarctica_Mawson
		, RT_TIMEZONE_Antarctica_Palmer
		, RT_TIMEZONE_Antarctica_Rothera
		, RT_TIMEZONE_Antarctica_Syowa
		, RT_TIMEZONE_Antarctica_Troll
		, RT_TIMEZONE_Antarctica_Vostok
		, RT_TIMEZONE_Asia_Almaty
		, RT_TIMEZONE_Asia_Amman
		, RT_TIMEZONE_Asia_Anadyr
		, RT_TIMEZONE_Asia_Aqtau
		, RT_TIMEZONE_Asia_Aqtobe
		, RT_TIMEZONE_Asia_Ashgabat
		, RT_TIMEZONE_Asia_Atyrau
		, RT_TIMEZONE_Asia_Baghdad
		, RT_TIMEZONE_Asia_Baku
		, RT_TIMEZONE_Asia_Bangkok
		, RT_TIMEZONE_Asia_Barnaul
		, RT_TIMEZONE_Asia_Beirut
		, RT_TIMEZONE_Asia_Bishkek
		, RT_TIMEZONE_Asia_Brunei
		, RT_TIMEZONE_Asia_Chita
		, RT_TIMEZONE_Asia_Choibalsan
		, RT_TIMEZONE_Asia_Colombo
		, RT_TIMEZONE_Asia_Damascus
		, RT_TIMEZONE_Asia_Dhaka
		, RT_TIMEZONE_Asia_Dili
		, RT_TIMEZONE_Asia_Dubai
		, RT_TIMEZONE_Asia_Dushanbe
		, RT_TIMEZONE_Asia_Famagusta
		, RT_TIMEZONE_Asia_Gaza
		, RT_TIMEZONE_Asia_Hebron
		, RT_TIMEZONE_Asia_Ho_Chi_Minh
		, RT_TIMEZONE_Asia_Hong_Kong
		, RT_TIMEZONE_Asia_Hovd
		, RT_TIMEZONE_Asia_Irkutsk
		, RT_TIMEZONE_Asia_Jakarta
		, RT_TIMEZONE_Asia_Jayapura
		, RT_TIMEZONE_Asia_Jerusalem
		, RT_TIMEZONE_Asia_Kabul
		, RT_TIMEZONE_Asia_Kamchatka
		, RT_TIMEZONE_Asia_Karachi
		, RT_TIMEZONE_Asia_Kathmandu
		, RT_TIMEZONE_Asia_Khandyga
		, RT_TIMEZONE_Asia_Kolkata
		, RT_TIMEZONE_Asia_Krasnoyarsk
		, RT_TIMEZONE_Asia_Kuala_Lumpur
		, RT_TIMEZONE_Asia_Kuching
		, RT_TIMEZONE_Asia_Macau
		, RT_TIMEZONE_Asia_Magadan
		, RT_TIMEZONE_Asia_Makassar
		, RT_TIMEZONE_Asia_Manila
		, RT_TIMEZONE_Asia_Nicosia
		, RT_TIMEZONE_Asia_Novokuznetsk
		, RT_TIMEZONE_Asia_Novosibirsk
		, RT_TIMEZONE_Asia_Omsk
		, RT_TIMEZONE_Asia_Oral
		, RT_TIMEZONE_Asia_Pontianak
		, RT_TIMEZONE_Asia_Pyongyang
		, RT_TIMEZONE_Asia_Qatar
		, RT_TIMEZONE_Asia_Qostanay
		, RT_TIMEZONE_Asia_Qyzylorda
		, RT_TIMEZONE_Asia_Riyadh
		, RT_TIMEZONE_Asia_Sakhalin
		, RT_TIMEZONE_Asia_Samarkand
		, RT_TIMEZONE_Asia_Seoul
		, RT_TIMEZONE_Asia_Shanghai
		, RT_TIMEZONE_Asia_Singapore
		, RT_TIMEZONE_Asia_Srednekolymsk
		, RT_TIMEZONE_Asia_Taipei
		, RT_TIMEZONE_Asia_Tashkent
		, RT_TIMEZONE_Asia_Tbilisi
		, RT_TIMEZONE_Asia_Tehran
		, RT_TIMEZONE_Asia_Thimphu
		, RT_TIMEZONE_Asia_Tokyo
		, RT_TIMEZONE_Asia_Tomsk
		, RT_TIMEZONE_Asia_Ulaanbaatar
		, RT_TIMEZONE_Asia_Urumqi
		, RT_TIMEZONE_Asia_Ust_Nera
		, RT_TIMEZONE_Asia_Vladivostok
		, RT_TIMEZONE_Asia_Yakutsk
		, RT_TIMEZONE_Asia_Yangon
		, RT_TIMEZONE_Asia_Yekaterinburg
		, RT_TIMEZONE_Asia_Yerevan
		, RT_TIMEZONE_Atlantic_Azores
		, RT_TIMEZONE_Atlantic_Bermuda
		, RT_TIMEZONE_Atlantic_Canary
		, RT_TIMEZONE_Atlantic_Cape_Verde
		, RT_TIMEZONE_Atlantic_Faroe
		, RT_TIMEZONE_Atlantic_Madeira
		, RT_TIMEZONE_Atlantic_Reykjavik
		, RT_TIMEZONE_Atlantic_South_Georgia
		, RT_TIMEZONE_Atlantic_Stanley
		, RT_TIMEZONE_Australia_Adelaide
		, RT_TIMEZONE_Australia_Brisbane
		, RT_TIMEZONE_Australia_Broken_Hill
		, RT_TIMEZONE_Australia_Currie
		, RT_TIMEZONE_Australia_Darwin
		, RT_TIMEZONE_Australia_Eucla
		, RT_TIMEZONE_Australia_Hobart
		, RT_TIMEZONE_Australia_Lindeman
		, RT_TIMEZONE_Australia_Lord_Howe
		, RT_TIMEZONE_Australia_Melbourne
		, RT_TIMEZONE_Australia_Perth
		, RT_TIMEZONE_Australia_Sydney
		, RT_TIMEZONE_CET
		, RT_TIMEZONE_CST6CDT
		, RT_TIMEZONE_EET
		, RT_TIMEZONE_EST
		, RT_TIMEZONE_EST5EDT
		, RT_TIMEZONE_Europe_Amsterdam
		, RT_TIMEZONE_Europe_Andorra
		, RT_TIMEZONE_Europe_Astrakhan
		, RT_TIMEZONE_Europe_Athens
		, RT_TIMEZONE_Europe_Belgrade
		, RT_TIMEZONE_Europe_Berlin
		, RT_TIMEZONE_Europe_Brussels
		, RT_TIMEZONE_Europe_Bucharest
		, RT_TIMEZONE_Europe_Budapest
		, RT_TIMEZONE_Europe_Chisinau
		, RT_TIMEZONE_Europe_Copenhagen
		, RT_TIMEZONE_Europe_Dublin
		, RT_TIMEZONE_Europe_Gibraltar
		, RT_TIMEZONE_Europe_Helsinki
		, RT_TIMEZONE_Europe_Istanbul
		, RT_TIMEZONE_Europe_Kaliningrad
		, RT_TIMEZONE_Europe_Kiev
		, RT_TIMEZONE_Europe_Kirov
		, RT_TIMEZONE_Europe_Lisbon
		, RT_TIMEZONE_Europe_London
		, RT_TIMEZONE_Europe_Luxembourg
		, RT_TIMEZONE_Europe_Madrid
		, RT_TIMEZONE_Europe_Malta
		, RT_TIMEZONE_Europe_Minsk
		, RT_TIMEZONE_Europe_Monaco
		, RT_TIMEZONE_Europe_Moscow
		, RT_TIMEZONE_Europe_Oslo
		, RT_TIMEZONE_Europe_Paris
		, RT_TIMEZONE_Europe_Prague
		, RT_TIMEZONE_Europe_Riga
		, RT_TIMEZONE_Europe_Rome
		, RT_TIMEZONE_Europe_Samara
		, RT_TIMEZONE_Europe_Saratov
		, RT_TIMEZONE_Europe_Simferopol
		, RT_TIMEZONE_Europe_Sofia
		, RT_TIMEZONE_Europe_Stockholm
		, RT_TIMEZONE_Europe_Tallinn
		, RT_TIMEZONE_Europe_Tirane
		, RT_TIMEZONE_Europe_Ulyanovsk
		, RT_TIMEZONE_Europe_Uzhgorod
		, RT_TIMEZONE_Europe_Vienna
		, RT_TIMEZONE_Europe_Vilnius
		, RT_TIMEZONE_Europe_Volgograd
		, RT_TIMEZONE_Europe_Warsaw
		, RT_TIMEZONE_Europe_Zaporozhye
		, RT_TIMEZONE_Europe_Zurich
		, RT_TIMEZONE_HST
		, RT_TIMEZONE_Indian_Chagos
		, RT_TIMEZONE_Indian_Christmas
		, RT_TIMEZONE_Indian_Cocos
		, RT_TIMEZONE_Indian_Kerguelen
		, RT_TIMEZONE_Indian_Mahe
		, RT_TIMEZONE_Indian_Maldives
		, RT_TIMEZONE_Indian_Mauritius
		, RT_TIMEZONE_Indian_Reunion
		, RT_TIMEZONE_MET
		, RT_TIMEZONE_MST
		, RT_TIMEZONE_MST7MDT
		, RT_TIMEZONE_PST8PDT
		, RT_TIMEZONE_Pacific_Apia
		, RT_TIMEZONE_Pacific_Auckland
		, RT_TIMEZONE_Pacific_Bougainville
		, RT_TIMEZONE_Pacific_Chatham
		, RT_TIMEZONE_Pacific_Chuuk
		, RT_TIMEZONE_Pacific_Easter
		, RT_TIMEZONE_Pacific_Efate
		, RT_TIMEZONE_Pacific_Enderbury
		, RT_TIMEZONE_Pacific_Fakaofo
		, RT_TIMEZONE_Pacific_Fiji
		, RT_TIMEZONE_Pacific_Funafuti
		, RT_TIMEZONE_Pacific_Galapagos
		, RT_TIMEZONE_Pacific_Gambier
		, RT_TIMEZONE_Pacific_Guadalcanal
		, RT_TIMEZONE_Pacific_Guam
		, RT_TIMEZONE_Pacific_Honolulu
		, RT_TIMEZONE_Pacific_Kiritimati
		, RT_TIMEZONE_Pacific_Kosrae
		, RT_TIMEZONE_Pacific_Kwajalein
		, RT_TIMEZONE_Pacific_Majuro
		, RT_TIMEZONE_Pacific_Marquesas
		, RT_TIMEZONE_Pacific_Nauru
		, RT_TIMEZONE_Pacific_Niue
		, RT_TIMEZONE_Pacific_Norfolk
		, RT_TIMEZONE_Pacific_Noumea
		, RT_TIMEZONE_Pacific_Pago_Pago
		, RT_TIMEZONE_Pacific_Palau
		, RT_TIMEZONE_Pacific_Pitcairn
		, RT_TIMEZONE_Pacific_Pohnpei
		, RT_TIMEZONE_Pacific_Port_Moresby
		, RT_TIMEZONE_Pacific_Rarotonga
		, RT_TIMEZONE_Pacific_Tahiti
		, RT_TIMEZONE_Pacific_Tarawa
		, RT_TIMEZONE_Pacific_Tongatapu
		, RT_TIMEZONE_Pacific_Wake
		, RT_TIMEZONE_Pacific_Wallis
		, RT_TIMEZONE_UTC
		, RT_TIMEZONE_WET
};

struct rt_user {
	char *id;
	char *name;
	char *password;
	char *emailaddress;
	char *realname;
	char *nickname;
	char *organization;
	char *address1;
	char *address2;
	char *city;
	char *state;
	char *zip;
	char *country;
	char *homephone;
	char *workphone;
	char *mobilephone;
	char *pagerphone;
	char *contactinfo;
	char *comments;
	char *signature;
	char *gecos;
	enum rt_lang lang;
	enum rt_timezone timezone;
	bool privileged;
	bool disabled;
};

#ifdef __cplusplus
extern "C" {
#endif

	void rtclient_user_show(struct rt_user **userptr, const char *name);
	void rtclient_user_new(const char *name
			, const char *password
			, const char *emailaddress
			, const char *realname
			, const char *nickname
			, const char *organization
			, const char *address1
			, const char *address2
			, const char *city
			, const char *state
			, const char *zip
			, const char *country
			, const char *homephone
			, const char *workphone
			, const char *mobilephone
			, const char *pagerphone
			, const char *contactinfo
			, const char *comments
			, const char *signature
			, const char *gecos
			, enum rt_lang lang
			, enum rt_timezone timezone
			, bool disabled
			, bool privileged);
	void rtclient_user_free(struct rt_user *user);

#ifdef __cplusplus
}
#endif

#endif // RTCLIENT_USER_H
