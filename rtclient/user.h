#ifndef RTCLIENT_USER_H
#define RTCLIENT_USER_H

enum rtclient_lang {
	RTCLIENT_LANG_NONE = 0
		, RTCLIENT_LANG_ar
		, RTCLIENT_LANG_eu
		, RTCLIENT_LANG_nb
		, RTCLIENT_LANG_bg
		, RTCLIENT_LANG_ca
		, RTCLIENT_LANG_zh_cn
		, RTCLIENT_LANG_zh_tw
		, RTCLIENT_LANG_hr
		, RTCLIENT_LANG_cs
		, RTCLIENT_LANG_da
		, RTCLIENT_LANG_nl
		, RTCLIENT_LANG_en
		, RTCLIENT_LANG_en_gb
		, RTCLIENT_LANG_et
		, RTCLIENT_LANG_fi
		, RTCLIENT_LANG_fr
		, RTCLIENT_LANG_de
		, RTCLIENT_LANG_el
		, RTCLIENT_LANG_hu
		, RTCLIENT_LANG_is
		, RTCLIENT_LANG_id
		, RTCLIENT_LANG_it
		, RTCLIENT_LANG_ja
		, RTCLIENT_LANG_lv
		, RTCLIENT_LANG_lt
		, RTCLIENT_LANG_nn
		, RTCLIENT_LANG_fa
		, RTCLIENT_LANG_pl
		, RTCLIENT_LANG_pt
		, RTCLIENT_LANG_pt_br
		, RTCLIENT_LANG_pt_pt
		, RTCLIENT_LANG_ro
		, RTCLIENT_LANG_ru
		, RTCLIENT_LANG_sr
		, RTCLIENT_LANG_sk
		, RTCLIENT_LANG_sl
		, RTCLIENT_LANG_es
		, RTCLIENT_LANG_sv
		, RTCLIENT_LANG_tr
};

enum rtclient_timezone {
	RTCLIENT_TIMEZONE_NONE = 0
		, RTCLIENT_TIMEZONE_Africa_Abidjan
		, RTCLIENT_TIMEZONE_Africa_Accra
		, RTCLIENT_TIMEZONE_Africa_Algiers
		, RTCLIENT_TIMEZONE_Africa_Bissau
		, RTCLIENT_TIMEZONE_Africa_Cairo
		, RTCLIENT_TIMEZONE_Africa_Casablanca
		, RTCLIENT_TIMEZONE_Africa_Ceuta
		, RTCLIENT_TIMEZONE_Africa_El_Aaiun
		, RTCLIENT_TIMEZONE_Africa_Johannesburg
		, RTCLIENT_TIMEZONE_Africa_Juba
		, RTCLIENT_TIMEZONE_Africa_Khartoum
		, RTCLIENT_TIMEZONE_Africa_Lagos
		, RTCLIENT_TIMEZONE_Africa_Maputo
		, RTCLIENT_TIMEZONE_Africa_Monrovia
		, RTCLIENT_TIMEZONE_Africa_Nairobi
		, RTCLIENT_TIMEZONE_Africa_Ndjamena
		, RTCLIENT_TIMEZONE_Africa_Sao_Tome
		, RTCLIENT_TIMEZONE_Africa_Tripoli
		, RTCLIENT_TIMEZONE_Africa_Tunis
		, RTCLIENT_TIMEZONE_Africa_Windhoek
		, RTCLIENT_TIMEZONE_America_Adak
		, RTCLIENT_TIMEZONE_America_Anchorage
		, RTCLIENT_TIMEZONE_America_Araguaina
		, RTCLIENT_TIMEZONE_America_Argentina_Buenos_Aires
		, RTCLIENT_TIMEZONE_America_Argentina_Catamarca
		, RTCLIENT_TIMEZONE_America_Argentina_Cordoba
		, RTCLIENT_TIMEZONE_America_Argentina_Jujuy
		, RTCLIENT_TIMEZONE_America_Argentina_La_Rioja
		, RTCLIENT_TIMEZONE_America_Argentina_Mendoza
		, RTCLIENT_TIMEZONE_America_Argentina_Rio_Gallegos
		, RTCLIENT_TIMEZONE_America_Argentina_Salta
		, RTCLIENT_TIMEZONE_America_Argentina_San_Juan
		, RTCLIENT_TIMEZONE_America_Argentina_San_Luis
		, RTCLIENT_TIMEZONE_America_Argentina_Tucuman
		, RTCLIENT_TIMEZONE_America_Argentina_Ushuaia
		, RTCLIENT_TIMEZONE_America_Asuncion
		, RTCLIENT_TIMEZONE_America_Atikokan
		, RTCLIENT_TIMEZONE_America_Bahia
		, RTCLIENT_TIMEZONE_America_Bahia_Banderas
		, RTCLIENT_TIMEZONE_America_Barbados
		, RTCLIENT_TIMEZONE_America_Belem
		, RTCLIENT_TIMEZONE_America_Belize
		, RTCLIENT_TIMEZONE_America_Blanc_Sablon
		, RTCLIENT_TIMEZONE_America_Boa_Vista
		, RTCLIENT_TIMEZONE_America_Bogota
		, RTCLIENT_TIMEZONE_America_Boise
		, RTCLIENT_TIMEZONE_America_Cambridge_Bay
		, RTCLIENT_TIMEZONE_America_Campo_Grande
		, RTCLIENT_TIMEZONE_America_Cancun
		, RTCLIENT_TIMEZONE_America_Caracas
		, RTCLIENT_TIMEZONE_America_Cayenne
		, RTCLIENT_TIMEZONE_America_Chicago
		, RTCLIENT_TIMEZONE_America_Chihuahua
		, RTCLIENT_TIMEZONE_America_Costa_Rica
		, RTCLIENT_TIMEZONE_America_Creston
		, RTCLIENT_TIMEZONE_America_Cuiaba
		, RTCLIENT_TIMEZONE_America_Curacao
		, RTCLIENT_TIMEZONE_America_Danmarkshavn
		, RTCLIENT_TIMEZONE_America_Dawson
		, RTCLIENT_TIMEZONE_America_Dawson_Creek
		, RTCLIENT_TIMEZONE_America_Denver
		, RTCLIENT_TIMEZONE_America_Detroit
		, RTCLIENT_TIMEZONE_America_Edmonton
		, RTCLIENT_TIMEZONE_America_Eirunepe
		, RTCLIENT_TIMEZONE_America_El_Salvador
		, RTCLIENT_TIMEZONE_America_Fortclient_Nelson
		, RTCLIENT_TIMEZONE_America_Fortaleza
		, RTCLIENT_TIMEZONE_America_Glace_Bay
		, RTCLIENT_TIMEZONE_America_Godthab
		, RTCLIENT_TIMEZONE_America_Goose_Bay
		, RTCLIENT_TIMEZONE_America_Grand_Turk
		, RTCLIENT_TIMEZONE_America_Guatemala
		, RTCLIENT_TIMEZONE_America_Guayaquil
		, RTCLIENT_TIMEZONE_America_Guyana
		, RTCLIENT_TIMEZONE_America_Halifax
		, RTCLIENT_TIMEZONE_America_Havana
		, RTCLIENT_TIMEZONE_America_Hermosillo
		, RTCLIENT_TIMEZONE_America_Indiana_Indianapolis
		, RTCLIENT_TIMEZONE_America_Indiana_Knox
		, RTCLIENT_TIMEZONE_America_Indiana_Marengo
		, RTCLIENT_TIMEZONE_America_Indiana_Petersburg
		, RTCLIENT_TIMEZONE_America_Indiana_Tell_City
		, RTCLIENT_TIMEZONE_America_Indiana_Vevay
		, RTCLIENT_TIMEZONE_America_Indiana_Vincennes
		, RTCLIENT_TIMEZONE_America_Indiana_Winamac
		, RTCLIENT_TIMEZONE_America_Inuvik
		, RTCLIENT_TIMEZONE_America_Iqaluit
		, RTCLIENT_TIMEZONE_America_Jamaica
		, RTCLIENT_TIMEZONE_America_Juneau
		, RTCLIENT_TIMEZONE_America_Kentucky_Louisville
		, RTCLIENT_TIMEZONE_America_Kentucky_Monticello
		, RTCLIENT_TIMEZONE_America_La_Paz
		, RTCLIENT_TIMEZONE_America_Lima
		, RTCLIENT_TIMEZONE_America_Los_Angeles
		, RTCLIENT_TIMEZONE_America_Maceio
		, RTCLIENT_TIMEZONE_America_Managua
		, RTCLIENT_TIMEZONE_America_Manaus
		, RTCLIENT_TIMEZONE_America_Martinique
		, RTCLIENT_TIMEZONE_America_Matamoros
		, RTCLIENT_TIMEZONE_America_Mazatlan
		, RTCLIENT_TIMEZONE_America_Menominee
		, RTCLIENT_TIMEZONE_America_Merida
		, RTCLIENT_TIMEZONE_America_Metlakatla
		, RTCLIENT_TIMEZONE_America_Mexico_City
		, RTCLIENT_TIMEZONE_America_Miquelon
		, RTCLIENT_TIMEZONE_America_Moncton
		, RTCLIENT_TIMEZONE_America_Monterrey
		, RTCLIENT_TIMEZONE_America_Montevideo
		, RTCLIENT_TIMEZONE_America_Nassau
		, RTCLIENT_TIMEZONE_America_New_York
		, RTCLIENT_TIMEZONE_America_Nipigon
		, RTCLIENT_TIMEZONE_America_Nome
		, RTCLIENT_TIMEZONE_America_Noronha
		, RTCLIENT_TIMEZONE_America_North_Dakota_Beulah
		, RTCLIENT_TIMEZONE_America_North_Dakota_Center
		, RTCLIENT_TIMEZONE_America_North_Dakota_New_Salem
		, RTCLIENT_TIMEZONE_America_Ojinaga
		, RTCLIENT_TIMEZONE_America_Panama
		, RTCLIENT_TIMEZONE_America_Pangnirtung
		, RTCLIENT_TIMEZONE_America_Paramaribo
		, RTCLIENT_TIMEZONE_America_Phoenix
		, RTCLIENT_TIMEZONE_America_Portclient_au_Prince
		, RTCLIENT_TIMEZONE_America_Portclient_of_Spain
		, RTCLIENT_TIMEZONE_America_Porto_Velho
		, RTCLIENT_TIMEZONE_America_Puerto_Rico
		, RTCLIENT_TIMEZONE_America_Punta_Arenas
		, RTCLIENT_TIMEZONE_America_Rainy_River
		, RTCLIENT_TIMEZONE_America_Rankin_Inlet
		, RTCLIENT_TIMEZONE_America_Recife
		, RTCLIENT_TIMEZONE_America_Regina
		, RTCLIENT_TIMEZONE_America_Resolute
		, RTCLIENT_TIMEZONE_America_Rio_Branco
		, RTCLIENT_TIMEZONE_America_Santarem
		, RTCLIENT_TIMEZONE_America_Santiago
		, RTCLIENT_TIMEZONE_America_Santo_Domingo
		, RTCLIENT_TIMEZONE_America_Sao_Paulo
		, RTCLIENT_TIMEZONE_America_Scoresbysund
		, RTCLIENT_TIMEZONE_America_Sitka
		, RTCLIENT_TIMEZONE_America_St_Johns
		, RTCLIENT_TIMEZONE_America_Swift_Current
		, RTCLIENT_TIMEZONE_America_Tegucigalpa
		, RTCLIENT_TIMEZONE_America_Thule
		, RTCLIENT_TIMEZONE_America_Thunder_Bay
		, RTCLIENT_TIMEZONE_America_Tijuana
		, RTCLIENT_TIMEZONE_America_Toronto
		, RTCLIENT_TIMEZONE_America_Vancouver
		, RTCLIENT_TIMEZONE_America_Whitehorse
		, RTCLIENT_TIMEZONE_America_Winnipeg
		, RTCLIENT_TIMEZONE_America_Yakutat
		, RTCLIENT_TIMEZONE_America_Yellowknife
		, RTCLIENT_TIMEZONE_Antarctica_Casey
		, RTCLIENT_TIMEZONE_Antarctica_Davis
		, RTCLIENT_TIMEZONE_Antarctica_DumontDUrville
		, RTCLIENT_TIMEZONE_Antarctica_Macquarie
		, RTCLIENT_TIMEZONE_Antarctica_Mawson
		, RTCLIENT_TIMEZONE_Antarctica_Palmer
		, RTCLIENT_TIMEZONE_Antarctica_Rothera
		, RTCLIENT_TIMEZONE_Antarctica_Syowa
		, RTCLIENT_TIMEZONE_Antarctica_Troll
		, RTCLIENT_TIMEZONE_Antarctica_Vostok
		, RTCLIENT_TIMEZONE_Asia_Almaty
		, RTCLIENT_TIMEZONE_Asia_Amman
		, RTCLIENT_TIMEZONE_Asia_Anadyr
		, RTCLIENT_TIMEZONE_Asia_Aqtau
		, RTCLIENT_TIMEZONE_Asia_Aqtobe
		, RTCLIENT_TIMEZONE_Asia_Ashgabat
		, RTCLIENT_TIMEZONE_Asia_Atyrau
		, RTCLIENT_TIMEZONE_Asia_Baghdad
		, RTCLIENT_TIMEZONE_Asia_Baku
		, RTCLIENT_TIMEZONE_Asia_Bangkok
		, RTCLIENT_TIMEZONE_Asia_Barnaul
		, RTCLIENT_TIMEZONE_Asia_Beirut
		, RTCLIENT_TIMEZONE_Asia_Bishkek
		, RTCLIENT_TIMEZONE_Asia_Brunei
		, RTCLIENT_TIMEZONE_Asia_Chita
		, RTCLIENT_TIMEZONE_Asia_Choibalsan
		, RTCLIENT_TIMEZONE_Asia_Colombo
		, RTCLIENT_TIMEZONE_Asia_Damascus
		, RTCLIENT_TIMEZONE_Asia_Dhaka
		, RTCLIENT_TIMEZONE_Asia_Dili
		, RTCLIENT_TIMEZONE_Asia_Dubai
		, RTCLIENT_TIMEZONE_Asia_Dushanbe
		, RTCLIENT_TIMEZONE_Asia_Famagusta
		, RTCLIENT_TIMEZONE_Asia_Gaza
		, RTCLIENT_TIMEZONE_Asia_Hebron
		, RTCLIENT_TIMEZONE_Asia_Ho_Chi_Minh
		, RTCLIENT_TIMEZONE_Asia_Hong_Kong
		, RTCLIENT_TIMEZONE_Asia_Hovd
		, RTCLIENT_TIMEZONE_Asia_Irkutsk
		, RTCLIENT_TIMEZONE_Asia_Jakarta
		, RTCLIENT_TIMEZONE_Asia_Jayapura
		, RTCLIENT_TIMEZONE_Asia_Jerusalem
		, RTCLIENT_TIMEZONE_Asia_Kabul
		, RTCLIENT_TIMEZONE_Asia_Kamchatka
		, RTCLIENT_TIMEZONE_Asia_Karachi
		, RTCLIENT_TIMEZONE_Asia_Kathmandu
		, RTCLIENT_TIMEZONE_Asia_Khandyga
		, RTCLIENT_TIMEZONE_Asia_Kolkata
		, RTCLIENT_TIMEZONE_Asia_Krasnoyarsk
		, RTCLIENT_TIMEZONE_Asia_Kuala_Lumpur
		, RTCLIENT_TIMEZONE_Asia_Kuching
		, RTCLIENT_TIMEZONE_Asia_Macau
		, RTCLIENT_TIMEZONE_Asia_Magadan
		, RTCLIENT_TIMEZONE_Asia_Makassar
		, RTCLIENT_TIMEZONE_Asia_Manila
		, RTCLIENT_TIMEZONE_Asia_Nicosia
		, RTCLIENT_TIMEZONE_Asia_Novokuznetsk
		, RTCLIENT_TIMEZONE_Asia_Novosibirsk
		, RTCLIENT_TIMEZONE_Asia_Omsk
		, RTCLIENT_TIMEZONE_Asia_Oral
		, RTCLIENT_TIMEZONE_Asia_Pontianak
		, RTCLIENT_TIMEZONE_Asia_Pyongyang
		, RTCLIENT_TIMEZONE_Asia_Qatar
		, RTCLIENT_TIMEZONE_Asia_Qostanay
		, RTCLIENT_TIMEZONE_Asia_Qyzylorda
		, RTCLIENT_TIMEZONE_Asia_Riyadh
		, RTCLIENT_TIMEZONE_Asia_Sakhalin
		, RTCLIENT_TIMEZONE_Asia_Samarkand
		, RTCLIENT_TIMEZONE_Asia_Seoul
		, RTCLIENT_TIMEZONE_Asia_Shanghai
		, RTCLIENT_TIMEZONE_Asia_Singapore
		, RTCLIENT_TIMEZONE_Asia_Srednekolymsk
		, RTCLIENT_TIMEZONE_Asia_Taipei
		, RTCLIENT_TIMEZONE_Asia_Tashkent
		, RTCLIENT_TIMEZONE_Asia_Tbilisi
		, RTCLIENT_TIMEZONE_Asia_Tehran
		, RTCLIENT_TIMEZONE_Asia_Thimphu
		, RTCLIENT_TIMEZONE_Asia_Tokyo
		, RTCLIENT_TIMEZONE_Asia_Tomsk
		, RTCLIENT_TIMEZONE_Asia_Ulaanbaatar
		, RTCLIENT_TIMEZONE_Asia_Urumqi
		, RTCLIENT_TIMEZONE_Asia_Ust_Nera
		, RTCLIENT_TIMEZONE_Asia_Vladivostok
		, RTCLIENT_TIMEZONE_Asia_Yakutsk
		, RTCLIENT_TIMEZONE_Asia_Yangon
		, RTCLIENT_TIMEZONE_Asia_Yekaterinburg
		, RTCLIENT_TIMEZONE_Asia_Yerevan
		, RTCLIENT_TIMEZONE_Atlantic_Azores
		, RTCLIENT_TIMEZONE_Atlantic_Bermuda
		, RTCLIENT_TIMEZONE_Atlantic_Canary
		, RTCLIENT_TIMEZONE_Atlantic_Cape_Verde
		, RTCLIENT_TIMEZONE_Atlantic_Faroe
		, RTCLIENT_TIMEZONE_Atlantic_Madeira
		, RTCLIENT_TIMEZONE_Atlantic_Reykjavik
		, RTCLIENT_TIMEZONE_Atlantic_South_Georgia
		, RTCLIENT_TIMEZONE_Atlantic_Stanley
		, RTCLIENT_TIMEZONE_Australia_Adelaide
		, RTCLIENT_TIMEZONE_Australia_Brisbane
		, RTCLIENT_TIMEZONE_Australia_Broken_Hill
		, RTCLIENT_TIMEZONE_Australia_Currie
		, RTCLIENT_TIMEZONE_Australia_Darwin
		, RTCLIENT_TIMEZONE_Australia_Eucla
		, RTCLIENT_TIMEZONE_Australia_Hobart
		, RTCLIENT_TIMEZONE_Australia_Lindeman
		, RTCLIENT_TIMEZONE_Australia_Lord_Howe
		, RTCLIENT_TIMEZONE_Australia_Melbourne
		, RTCLIENT_TIMEZONE_Australia_Perth
		, RTCLIENT_TIMEZONE_Australia_Sydney
		, RTCLIENT_TIMEZONE_CET
		, RTCLIENT_TIMEZONE_CST6CDT
		, RTCLIENT_TIMEZONE_EET
		, RTCLIENT_TIMEZONE_EST
		, RTCLIENT_TIMEZONE_EST5EDT
		, RTCLIENT_TIMEZONE_Europe_Amsterdam
		, RTCLIENT_TIMEZONE_Europe_Andorra
		, RTCLIENT_TIMEZONE_Europe_Astrakhan
		, RTCLIENT_TIMEZONE_Europe_Athens
		, RTCLIENT_TIMEZONE_Europe_Belgrade
		, RTCLIENT_TIMEZONE_Europe_Berlin
		, RTCLIENT_TIMEZONE_Europe_Brussels
		, RTCLIENT_TIMEZONE_Europe_Bucharest
		, RTCLIENT_TIMEZONE_Europe_Budapest
		, RTCLIENT_TIMEZONE_Europe_Chisinau
		, RTCLIENT_TIMEZONE_Europe_Copenhagen
		, RTCLIENT_TIMEZONE_Europe_Dublin
		, RTCLIENT_TIMEZONE_Europe_Gibraltar
		, RTCLIENT_TIMEZONE_Europe_Helsinki
		, RTCLIENT_TIMEZONE_Europe_Istanbul
		, RTCLIENT_TIMEZONE_Europe_Kaliningrad
		, RTCLIENT_TIMEZONE_Europe_Kiev
		, RTCLIENT_TIMEZONE_Europe_Kirov
		, RTCLIENT_TIMEZONE_Europe_Lisbon
		, RTCLIENT_TIMEZONE_Europe_London
		, RTCLIENT_TIMEZONE_Europe_Luxembourg
		, RTCLIENT_TIMEZONE_Europe_Madrid
		, RTCLIENT_TIMEZONE_Europe_Malta
		, RTCLIENT_TIMEZONE_Europe_Minsk
		, RTCLIENT_TIMEZONE_Europe_Monaco
		, RTCLIENT_TIMEZONE_Europe_Moscow
		, RTCLIENT_TIMEZONE_Europe_Oslo
		, RTCLIENT_TIMEZONE_Europe_Paris
		, RTCLIENT_TIMEZONE_Europe_Prague
		, RTCLIENT_TIMEZONE_Europe_Riga
		, RTCLIENT_TIMEZONE_Europe_Rome
		, RTCLIENT_TIMEZONE_Europe_Samara
		, RTCLIENT_TIMEZONE_Europe_Saratov
		, RTCLIENT_TIMEZONE_Europe_Simferopol
		, RTCLIENT_TIMEZONE_Europe_Sofia
		, RTCLIENT_TIMEZONE_Europe_Stockholm
		, RTCLIENT_TIMEZONE_Europe_Tallinn
		, RTCLIENT_TIMEZONE_Europe_Tirane
		, RTCLIENT_TIMEZONE_Europe_Ulyanovsk
		, RTCLIENT_TIMEZONE_Europe_Uzhgorod
		, RTCLIENT_TIMEZONE_Europe_Vienna
		, RTCLIENT_TIMEZONE_Europe_Vilnius
		, RTCLIENT_TIMEZONE_Europe_Volgograd
		, RTCLIENT_TIMEZONE_Europe_Warsaw
		, RTCLIENT_TIMEZONE_Europe_Zaporozhye
		, RTCLIENT_TIMEZONE_Europe_Zurich
		, RTCLIENT_TIMEZONE_HST
		, RTCLIENT_TIMEZONE_Indian_Chagos
		, RTCLIENT_TIMEZONE_Indian_Christmas
		, RTCLIENT_TIMEZONE_Indian_Cocos
		, RTCLIENT_TIMEZONE_Indian_Kerguelen
		, RTCLIENT_TIMEZONE_Indian_Mahe
		, RTCLIENT_TIMEZONE_Indian_Maldives
		, RTCLIENT_TIMEZONE_Indian_Mauritius
		, RTCLIENT_TIMEZONE_Indian_Reunion
		, RTCLIENT_TIMEZONE_MET
		, RTCLIENT_TIMEZONE_MST
		, RTCLIENT_TIMEZONE_MST7MDT
		, RTCLIENT_TIMEZONE_PST8PDT
		, RTCLIENT_TIMEZONE_Pacific_Apia
		, RTCLIENT_TIMEZONE_Pacific_Auckland
		, RTCLIENT_TIMEZONE_Pacific_Bougainville
		, RTCLIENT_TIMEZONE_Pacific_Chatham
		, RTCLIENT_TIMEZONE_Pacific_Chuuk
		, RTCLIENT_TIMEZONE_Pacific_Easter
		, RTCLIENT_TIMEZONE_Pacific_Efate
		, RTCLIENT_TIMEZONE_Pacific_Enderbury
		, RTCLIENT_TIMEZONE_Pacific_Fakaofo
		, RTCLIENT_TIMEZONE_Pacific_Fiji
		, RTCLIENT_TIMEZONE_Pacific_Funafuti
		, RTCLIENT_TIMEZONE_Pacific_Galapagos
		, RTCLIENT_TIMEZONE_Pacific_Gambier
		, RTCLIENT_TIMEZONE_Pacific_Guadalcanal
		, RTCLIENT_TIMEZONE_Pacific_Guam
		, RTCLIENT_TIMEZONE_Pacific_Honolulu
		, RTCLIENT_TIMEZONE_Pacific_Kiritimati
		, RTCLIENT_TIMEZONE_Pacific_Kosrae
		, RTCLIENT_TIMEZONE_Pacific_Kwajalein
		, RTCLIENT_TIMEZONE_Pacific_Majuro
		, RTCLIENT_TIMEZONE_Pacific_Marquesas
		, RTCLIENT_TIMEZONE_Pacific_Nauru
		, RTCLIENT_TIMEZONE_Pacific_Niue
		, RTCLIENT_TIMEZONE_Pacific_Norfolk
		, RTCLIENT_TIMEZONE_Pacific_Noumea
		, RTCLIENT_TIMEZONE_Pacific_Pago_Pago
		, RTCLIENT_TIMEZONE_Pacific_Palau
		, RTCLIENT_TIMEZONE_Pacific_Pitcairn
		, RTCLIENT_TIMEZONE_Pacific_Pohnpei
		, RTCLIENT_TIMEZONE_Pacific_Portclient_Moresby
		, RTCLIENT_TIMEZONE_Pacific_Rarotonga
		, RTCLIENT_TIMEZONE_Pacific_Tahiti
		, RTCLIENT_TIMEZONE_Pacific_Tarawa
		, RTCLIENT_TIMEZONE_Pacific_Tongatapu
		, RTCLIENT_TIMEZONE_Pacific_Wake
		, RTCLIENT_TIMEZONE_Pacific_Wallis
		, RTCLIENT_TIMEZONE_UTC
		, RTCLIENT_TIMEZONE_WET
};

struct rtclient_user {
	unsigned int id;
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
	enum rtclient_lang lang;
	enum rtclient_timezone timezone;
	bool privileged;
	bool disabled;
};

#ifdef __cplusplus
extern "C" {
#endif

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
			, enum rtclient_lang lang
			, enum rtclient_timezone timezone
			, bool disabled
			, bool privileged);
	void rtclient_user_showid(struct rtclient_user **userptr, unsigned int id);
	void rtclient_user_showname(struct rtclient_user **userptr, const char *name);
	void rtclient_user_free(struct rtclient_user *user);

#ifdef __cplusplus
}
#endif

#endif // RTCLIENT_USER_H
