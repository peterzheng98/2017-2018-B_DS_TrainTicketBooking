//
// Created by Peter Zheng on 2018/04/10.
// Filled by FineArtz on 2018/05/24.
//

#ifndef INC_2018DATASTRUCTUREBIGWORK_KERNEL_HPP
#define INC_2018DATASTRUCTUREBIGWORK_KERNEL_HPP

#include <cstdio>
#include "CoreData.h"
#include "BigNum.hpp"
#include "String.h"
#include "Set.hpp"
#include "BPlusTree.hpp"
#include "DateAndTime.h"
#include "Vector.h"
//#include "InternalData.h"
using namespace myAlgorithm;

namespace Kernel {
    class Interface;

    class Insert;

    class Select;

    class Update;

    class Delete;
}

class ticketKey;

class ticket {
    friend class ticketKey;

    friend class Kernel::Insert;

    friend class Kernel::Select;

    friend class Kernel::Update;

    friend class Kernel::Delete;

private:
    Pair<short, short> tk_position;
    Pair<Time, Time> tk_time;
    Date tk_date;
    short tk_catalog;
    int tk_ticketID;
    String tk_trainID;
    float tk_price[5];
    int tk_remain[5];
public:
    ticket() = default;

    ticket(const ticket &tik)
            : tk_position(tik.tk_position), tk_time(tik.tk_time), tk_date(tik.tk_date),
              tk_catalog(tik.tk_catalog), tk_ticketID(tik.tk_ticketID), tk_trainID(tk_trainID) {
        for (int i = 0; i < 5; ++i) {
            tk_price[i] = tik.tk_price[i];
            tk_remain[i] = tik.tk_remain[i];
        }
    }

    Pair<short, short> M_position() const {
        return tk_position;
    }

    Pair<Time, Time> M_time() const {
        return tk_time;
    }

    Date M_date() const {
        return tk_date;
    }

    short M_catalog() const {
        return tk_catalog;
    }

    String M_trainID() const {
        return tk_trainID;
    }

    const float *M_price() const {
        return tk_price;
    }

    const int *M_remain() const {
        return tk_remain;
    }
};

class ticketKey {
private:
    Pair<short, short> station;
    String trainID;
    Date date;
public:
    ticketKey() = default;

    ticketKey(const Pair<short, short> &stt, const Date &dt)
            : station(stt), date(dt) {}

    ticketKey(const Pair<short, short> &stt, const String &tid, const Date &dt)
            : station(stt), trainID(tid), date(dt) {}

    ticketKey(const ticket &tk)
            : station(tk.tk_position), trainID(tk.tk_trainID) {}

    bool operator<(const ticketKey &tk) const {
        return station < tk.station || (station == tk.station && date < tk.date)
               || (station == tk.station && date < tk.date && trainID < tk.trainID);
    }

    Pair<short, short> first() const {
        return station;
    }

    Date second() const {
        return date;
    }
};

class train {
    friend class Kernel::Insert;

    friend class Kernel::Select;

    friend class Kernel::Update;

    friend class Kernel::Delete;

private:
    String t_id;
    String t_name;
    short t_station[60];
    Time t_time[60];
    float t_price[60][5];
    short t_stationNum;
    short t_ticketKind;
    short t_ticketName[5];
    short t_catalog;
    bool t_onSale;
public:
    train() = default;

    train(const train &tr)
            : t_id(tr.t_id), t_name(tr.t_name), t_stationNum(tr.t_stationNum), t_ticketKind(tr.t_ticketKind),
              t_catalog(tr.t_catalog), t_onSale(tr.t_onSale) {
        for (short i = 0; i < t_stationNum; ++i) {
            t_station[i] = tr.t_station[i];
            t_time[i] = tr.t_time[i];
            for (short j = 0; j < t_ticketKind; ++j)
                t_price[i][j] = tr.t_price[i][j];
        }
        for (short j = 0; j < t_ticketKind; ++j)
            t_ticketName[j] = tr.t_ticketName[j];
    }

    String M_id() const {
        return t_id;
    }

    String M_name() const {
        return t_name;
    }

    const short *M_station() const {
        return t_station;
    }

    short M_stationNum() const {
        return t_stationNum;
    }

    short M_catalog() const {
        return t_catalog;
    }

    bool M_isOnSale() const {
        return t_onSale;
    }
};

class user {
    friend class Kernel::Select;

    friend class Kernel::Update;

private:
    int p_id;
    String p_username;
    String p_password;
    String p_email;
    String p_phone;
    UserPrivilege p_userPrivilege;
public:
    user() = default;

    user(int id, const String &nme, const String &pwd, const String &eml, const String &phn)
            : p_id(id), p_username(nme), p_password(pwd), p_email(eml), p_phone(phn) {
        p_userPrivilege = (id == 2018 ? Admin : User);
    }

    user(const user &rhs) {
        p_id = rhs.p_id;
        p_username = rhs.p_username;
        p_password = rhs.p_password;
        p_email = rhs.p_email;
        p_phone = rhs.p_phone;
        p_userPrivilege = rhs.p_userPrivilege;
    }

    user &operator=(const user &rhs) {
        if (this == &rhs) return *this;
        p_id = rhs.M_id();
        p_username = rhs.M_username();
        p_password = rhs.M_password();
        p_email = rhs.M_email();
        p_phone = rhs.M_phone();
        p_userPrivilege = rhs.M_privilege();
        return *this;
    }

    int M_id() const {
        return p_id;
    }

    String M_username() const {
        return p_username;
    }

    String M_password() const {
        return p_password;
    }

    String M_email() const {
        return p_email;
    }

    String M_phone() const {
        return p_phone;
    }

    UserPrivilege M_privilege() const {
        return p_userPrivilege;
    }
};

static int nowId = 2018;
static int ticketId = 1;
static Date startDate(2018, 6, 1), endDate(2018, 6, 30);

BPlusTree<int, user> userIdTree(false, "user.dat");
//BPlusTree<String, int> userNameTree(true, "userName.dat");
BPlusTree<ticketKey, ticket> ticketTree(false, "ticket.dat");
BPlusTree<int, ticket> ticketIdTree(false, "ticketId.dat");
BPlusTree<Pair<int, int>, Pair<int, int>> userTicketTree(false, "userTicket.dat");
BPlusTree<String, train> trainTree(false, "train.dat");

namespace Kernel {
    inline short hash2Short(const short &hash) {
        if (hash == 201468)return 0;
        if (hash == 194875)return 1;
        if (hash == 168288)return 2;
        if (hash == 70603)return 3;
        if (hash == 67222)return 4;
        if (hash == 95101)return 5;
        if (hash == 160483)return 6;
        if (hash == 6153)return 7;
        if (hash == 72512)return 8;
        if (hash == 153284)return 9;
        if (hash == 89232)return 10;
        if (hash == 56564)return 11;
        if (hash == 127376)return 12;
        if (hash == 167216)return 13;
        if (hash == 172910)return 14;
        if (hash == 101341)return 15;
        if (hash == 35122)return 16;
        if (hash == 57561)return 17;
        if (hash == 91048)return 18;
        if (hash == 3456)return 19;
        if (hash == 89876)return 20;
        if (hash == 146745)return 21;
        if (hash == 54803)return 22;
        if (hash == 24587)return 23;
        if (hash == 62799)return 24;
        if (hash == 49905)return 25;
        if (hash == 140280)return 26;
        if (hash == 157824)return 27;
        if (hash == 22444)return 28;
        if (hash == 7348)return 29;
        if (hash == 158795)return 30;
        if (hash == 178665)return 31;
        if (hash == 148461)return 32;
        if (hash == 112133)return 33;
        if (hash == 91884)return 34;
        if (hash == 114174)return 35;
        if (hash == 115932)return 36;
        if (hash == 137958)return 37;
        if (hash == 156360)return 38;
        if (hash == 167220)return 39;
        if (hash == 1407)return 40;
        if (hash == 55638)return 41;
        if (hash == 59813)return 42;
        if (hash == 1991)return 43;
        if (hash == 52531)return 44;
        if (hash == 51394)return 45;
        if (hash == 6094)return 46;
        if (hash == 135538)return 47;
        if (hash == 164416)return 48;
        if (hash == 31019)return 49;
        if (hash == 123173)return 50;
        if (hash == 2183)return 51;
        if (hash == 195652)return 52;
        if (hash == 94476)return 53;
        if (hash == 202259)return 54;
        if (hash == 66724)return 55;
        if (hash == 150836)return 56;
        if (hash == 187463)return 57;
        if (hash == 204169)return 58;
        if (hash == 184535)return 59;
        if (hash == 130187)return 60;
        if (hash == 67538)return 61;
        if (hash == 47249)return 62;
        if (hash == 187410)return 63;
        if (hash == 54013)return 64;
        if (hash == 29299)return 65;
        if (hash == 112510)return 66;
        if (hash == 2096)return 67;
        if (hash == 38266)return 68;
        if (hash == 23185)return 69;
        if (hash == 196301)return 70;
        if (hash == 22780)return 71;
        if (hash == 198226)return 72;
        if (hash == 46097)return 73;
        if (hash == 46054)return 74;
        if (hash == 129582)return 75;
        if (hash == 73929)return 76;
        if (hash == 99349)return 77;
        if (hash == 92271)return 78;
        if (hash == 104208)return 79;
        if (hash == 102759)return 80;
        if (hash == 201313)return 81;
        if (hash == 24815)return 82;
        if (hash == 63018)return 83;
        if (hash == 166549)return 84;
        if (hash == 48568)return 85;
        if (hash == 182500)return 86;
        if (hash == 138432)return 87;
        if (hash == 171189)return 88;
        if (hash == 147167)return 89;
        if (hash == 193428)return 90;
        if (hash == 193347)return 91;
        if (hash == 185906)return 92;
        if (hash == 107585)return 93;
        if (hash == 202168)return 94;
        if (hash == 132956)return 95;
        if (hash == 111147)return 96;
        if (hash == 120893)return 97;
        if (hash == 74912)return 98;
        if (hash == 183512)return 99;
        if (hash == 44713)return 100;
        if (hash == 161951)return 101;
        if (hash == 87388)return 102;
        if (hash == 177524)return 103;
        if (hash == 168879)return 104;
        if (hash == 10083)return 105;
        if (hash == 24163)return 106;
        if (hash == 11358)return 107;
        if (hash == 193455)return 108;
        if (hash == 113125)return 109;
        if (hash == 196617)return 110;
        if (hash == 32330)return 111;
        if (hash == 121168)return 112;
        if (hash == 30552)return 113;
        if (hash == 106993)return 114;
        if (hash == 99249)return 115;
        if (hash == 91858)return 116;
        if (hash == 61657)return 117;
        if (hash == 105049)return 118;
        if (hash == 49096)return 119;
        if (hash == 116130)return 120;
        if (hash == 92946)return 121;
        if (hash == 155586)return 122;
        if (hash == 108903)return 123;
        if (hash == 104731)return 124;
        if (hash == 122434)return 125;
        if (hash == 55011)return 126;
        if (hash == 78059)return 127;
        if (hash == 20190)return 128;
        if (hash == 180816)return 129;
        if (hash == 168222)return 130;
        if (hash == 123928)return 131;
        if (hash == 134466)return 132;
        if (hash == 168191)return 133;
        if (hash == 118873)return 134;
        if (hash == 153155)return 135;
        if (hash == 153106)return 136;
        if (hash == 138000)return 137;
        if (hash == 27936)return 138;
        if (hash == 107814)return 139;
        if (hash == 62576)return 140;
        if (hash == 176217)return 141;
        if (hash == 50640)return 142;
        if (hash == 21193)return 143;
        if (hash == 30180)return 144;
        if (hash == 164716)return 145;
        if (hash == 168187)return 146;
        if (hash == 142308)return 147;
        if (hash == 129050)return 148;
        if (hash == 105261)return 149;
        if (hash == 171369)return 150;
        if (hash == 150129)return 151;
        if (hash == 74628)return 152;
        if (hash == 59553)return 153;
        if (hash == 11281)return 154;
        if (hash == 34207)return 155;
        if (hash == 125431)return 156;
        if (hash == 185621)return 157;
        if (hash == 20836)return 158;
        if (hash == 67707)return 159;
        if (hash == 136447)return 160;
        if (hash == 155568)return 161;
        if (hash == 168642)return 162;
        if (hash == 66966)return 163;
        if (hash == 58784)return 164;
        if (hash == 124998)return 165;
        if (hash == 106836)return 166;
        if (hash == 194366)return 167;
        if (hash == 112682)return 168;
        if (hash == 168125)return 169;
        if (hash == 147460)return 170;
        if (hash == 138971)return 171;
        if (hash == 108031)return 172;
        if (hash == 122881)return 173;
        if (hash == 144568)return 174;
        if (hash == 53210)return 175;
        if (hash == 100934)return 176;
        if (hash == 52895)return 177;
        if (hash == 57234)return 178;
        if (hash == 93237)return 179;
        if (hash == 81069)return 180;
        if (hash == 41651)return 181;
        if (hash == 172529)return 182;
        if (hash == 6506)return 183;
        if (hash == 131404)return 184;
        if (hash == 29787)return 185;
        if (hash == 80154)return 186;
        if (hash == 141198)return 187;
        if (hash == 38215)return 188;
        if (hash == 91353)return 189;
        if (hash == 86562)return 190;
        if (hash == 80386)return 191;
        if (hash == 59811)return 192;
        if (hash == 111218)return 193;
        if (hash == 166328)return 194;
        if (hash == 104886)return 195;
        if (hash == 76304)return 196;
        if (hash == 141498)return 197;
        if (hash == 44746)return 198;
        if (hash == 48860)return 199;
        if (hash == 24976)return 200;
        if (hash == 95033)return 201;
        if (hash == 114747)return 202;
        if (hash == 16538)return 203;
        if (hash == 147452)return 204;
        if (hash == 28055)return 205;
        if (hash == 108304)return 206;
        if (hash == 198712)return 207;
        if (hash == 99083)return 208;
        if (hash == 161590)return 209;
        if (hash == 176183)return 210;
        if (hash == 155447)return 211;
        if (hash == 22991)return 212;
        if (hash == 199175)return 213;
        if (hash == 157443)return 214;
        if (hash == 182736)return 215;
        if (hash == 97734)return 216;
        if (hash == 199766)return 217;
        if (hash == 114230)return 218;
        if (hash == 192434)return 219;
        if (hash == 108143)return 220;
        if (hash == 93061)return 221;
        if (hash == 161432)return 222;
        if (hash == 104693)return 223;
        if (hash == 200359)return 224;
        if (hash == 186073)return 225;
        if (hash == 143166)return 226;
        if (hash == 112987)return 227;
        if (hash == 932)return 228;
        if (hash == 180437)return 229;
        if (hash == 180417)return 230;
        if (hash == 199709)return 231;
        if (hash == 60211)return 232;
        if (hash == 84256)return 233;
        if (hash == 117682)return 234;
        if (hash == 51115)return 235;
        if (hash == 156144)return 236;
        if (hash == 186698)return 237;
        if (hash == 140347)return 238;
        if (hash == 43591)return 239;
        if (hash == 30216)return 240;
        if (hash == 25392)return 241;
        if (hash == 73350)return 242;
        if (hash == 181578)return 243;
        if (hash == 114910)return 244;
        if (hash == 34668)return 245;
        if (hash == 142668)return 246;
        if (hash == 116016)return 247;
        if (hash == 72612)return 248;
        if (hash == 54514)return 249;
        if (hash == 107980)return 250;
        if (hash == 162451)return 251;
        if (hash == 125827)return 252;
        if (hash == 109158)return 253;
        if (hash == 141800)return 254;
        if (hash == 123596)return 255;
        if (hash == 142122)return 256;
        if (hash == 193634)return 257;
        if (hash == 166174)return 258;
        if (hash == 67667)return 259;
        if (hash == 185861)return 260;
        if (hash == 132535)return 261;
        if (hash == 195832)return 262;
        if (hash == 69220)return 263;
        if (hash == 156319)return 264;
        if (hash == 75264)return 265;
        if (hash == 111009)return 266;
        if (hash == 25271)return 267;
        if (hash == 119880)return 268;
        if (hash == 50139)return 269;
        if (hash == 161257)return 270;
        if (hash == 85920)return 271;
        if (hash == 130855)return 272;
        if (hash == 180664)return 273;
        if (hash == 83009)return 274;
        if (hash == 149154)return 275;
        if (hash == 169702)return 276;
        if (hash == 72026)return 277;
        if (hash == 157543)return 278;
        if (hash == 56934)return 279;
        if (hash == 928)return 280;
        if (hash == 92990)return 281;
        if (hash == 79045)return 282;
        if (hash == 156752)return 283;
        if (hash == 74250)return 284;
        if (hash == 201035)return 285;
        if (hash == 139199)return 286;
        if (hash == 129626)return 287;
        if (hash == 19854)return 288;
        if (hash == 111940)return 289;
        if (hash == 83023)return 290;
        if (hash == 84652)return 291;
        if (hash == 23588)return 292;
        if (hash == 177962)return 293;
        if (hash == 104484)return 294;
        if (hash == 38988)return 295;
        if (hash == 113163)return 296;
        if (hash == 116596)return 297;
        if (hash == 185243)return 298;
        if (hash == 127438)return 299;
        if (hash == 175231)return 300;
        if (hash == 204236)return 301;
        if (hash == 79409)return 302;
        if (hash == 103242)return 303;
        if (hash == 16595)return 304;
        if (hash == 190726)return 305;
        if (hash == 167044)return 306;
        if (hash == 123344)return 307;
        if (hash == 191805)return 308;
        if (hash == 11071)return 309;
        if (hash == 80475)return 310;
        if (hash == 172304)return 311;
        if (hash == 146396)return 312;
        if (hash == 92451)return 313;
        if (hash == 31771)return 314;
        if (hash == 103836)return 315;
        if (hash == 17867)return 316;
        if (hash == 184705)return 317;
        if (hash == 64481)return 318;
        if (hash == 139292)return 319;
        if (hash == 46081)return 320;
        if (hash == 135308)return 321;
        if (hash == 113616)return 322;
        if (hash == 122885)return 323;
        if (hash == 5669)return 324;
        if (hash == 98563)return 325;
        if (hash == 190728)return 326;
        if (hash == 19211)return 327;
        if (hash == 89204)return 328;
        if (hash == 115694)return 329;
        if (hash == 166530)return 330;
        if (hash == 33029)return 331;
        if (hash == 1942)return 332;
        if (hash == 1920)return 333;
        if (hash == 130706)return 334;
        if (hash == 34817)return 335;
        if (hash == 180517)return 336;
        if (hash == 132704)return 337;
        if (hash == 79005)return 338;
        if (hash == 140306)return 339;
        if (hash == 104458)return 340;
        if (hash == 128464)return 341;
        if (hash == 89244)return 342;
        if (hash == 200616)return 343;
        if (hash == 55216)return 344;
        if (hash == 169948)return 345;
        if (hash == 156575)return 346;
        if (hash == 148584)return 347;
        if (hash == 126163)return 348;
        if (hash == 12779)return 349;
        if (hash == 28480)return 350;
        if (hash == 172394)return 351;
        if (hash == 150218)return 352;
        if (hash == 1420)return 353;
        if (hash == 40503)return 354;
        if (hash == 188363)return 355;
        if (hash == 191679)return 356;
        if (hash == 185188)return 357;
        if (hash == 159652)return 358;
        if (hash == 108221)return 359;
        if (hash == 69385)return 360;
        if (hash == 168464)return 361;
        if (hash == 155639)return 362;
        if (hash == 140543)return 363;
        if (hash == 101860)return 364;
        if (hash == 56524)return 365;
        if (hash == 61192)return 366;
        if (hash == 153499)return 367;
        if (hash == 20767)return 368;
        if (hash == 14928)return 369;
        if (hash == 86126)return 370;
        if (hash == 29227)return 371;
        if (hash == 93123)return 372;
        if (hash == 77459)return 373;
        if (hash == 2018)return 374;
        if (hash == 154617)return 375;
        if (hash == 26507)return 376;
        if (hash == 26524)return 377;
        if (hash == 117260)return 378;
        if (hash == 141458)return 379;
        if (hash == 111110)return 380;
        if (hash == 179711)return 381;
        if (hash == 82758)return 382;
        if (hash == 105950)return 383;
        if (hash == 457)return 384;
        if (hash == 118460)return 385;
        if (hash == 38760)return 386;
        if (hash == 10149)return 387;
        if (hash == 99886)return 388;
        if (hash == 134209)return 389;
        if (hash == 36579)return 390;
        if (hash == 22095)return 391;
        if (hash == 116809)return 392;
        if (hash == 42554)return 393;
        if (hash == 53807)return 394;
        if (hash == 14596)return 395;
        if (hash == 50294)return 396;
        if (hash == 87223)return 397;
        if (hash == 47261)return 398;
        if (hash == 2045)return 399;
        if (hash == 17698)return 400;
        if (hash == 183670)return 401;
        if (hash == 6534)return 402;
        if (hash == 73084)return 403;
        if (hash == 114291)return 404;
        if (hash == 20578)return 405;
        if (hash == 122813)return 406;
        if (hash == 24938)return 407;
        if (hash == 16449)return 408;
        if (hash == 5098)return 409;
        if (hash == 103652)return 410;
        if (hash == 121292)return 411;
        if (hash == 28989)return 412;
        if (hash == 99200)return 413;
        if (hash == 190480)return 414;
        if (hash == 197087)return 415;
        if (hash == 60829)return 416;
        if (hash == 60825)return 417;
        if (hash == 15499)return 418;
        if (hash == 127500)return 419;
        if (hash == 427)return 420;
        if (hash == 62530)return 421;
        if (hash == 161326)return 422;
        if (hash == 10007)return 423;
        if (hash == 123713)return 424;
        if (hash == 132387)return 425;
        if (hash == 46439)return 426;
        if (hash == 199664)return 427;
        if (hash == 189845)return 428;
        if (hash == 115103)return 429;
        if (hash == 181028)return 430;
        if (hash == 11965)return 431;
        if (hash == 146458)return 432;
        if (hash == 90901)return 433;
        if (hash == 14110)return 434;
        if (hash == 169267)return 435;
        if (hash == 47410)return 436;
        if (hash == 109434)return 437;
        if (hash == 87205)return 438;
        if (hash == 18508)return 439;
        if (hash == 109788)return 440;
        if (hash == 110914)return 441;
        if (hash == 184590)return 442;
        if (hash == 140890)return 443;
        if (hash == 181184)return 444;
        if (hash == 150996)return 445;
        if (hash == 81204)return 446;
        if (hash == 135937)return 447;
        if (hash == 189019)return 448;
        if (hash == 110512)return 449;
        if (hash == 70178)return 450;
        if (hash == 196646)return 451;
        if (hash == 38020)return 452;
        if (hash == 765)return 453;
        if (hash == 64939)return 454;
        if (hash == 64437)return 455;
        if (hash == 129498)return 456;
        if (hash == 182840)return 457;
        if (hash == 16529)return 458;
        if (hash == 114416)return 459;
        if (hash == 108528)return 460;
        if (hash == 113609)return 461;
        if (hash == 122437)return 462;
        if (hash == 107319)return 463;
        if (hash == 112345)return 464;
        if (hash == 161339)return 465;
        if (hash == 107196)return 466;
        if (hash == 100944)return 467;
        if (hash == 115141)return 468;
        if (hash == 25450)return 469;
        if (hash == 192422)return 470;
        if (hash == 167801)return 471;
        if (hash == 192417)return 472;
        if (hash == 125324)return 473;
        if (hash == 147105)return 474;
        if (hash == 170195)return 475;
        if (hash == 44357)return 476;
        if (hash == 29828)return 477;
        if (hash == 73949)return 478;
        if (hash == 100361)return 479;
        if (hash == 63191)return 480;
        if (hash == 75576)return 481;
        if (hash == 30274)return 482;
        if (hash == 121749)return 483;
        if (hash == 192628)return 484;
        if (hash == 114428)return 485;
        if (hash == 106651)return 486;
        if (hash == 76508)return 487;
        if (hash == 46298)return 488;
        if (hash == 129897)return 489;
        if (hash == 84820)return 490;
        if (hash == 152749)return 491;
        if (hash == 164871)return 492;
        if (hash == 86475)return 493;
        if (hash == 136234)return 494;
        if (hash == 192168)return 495;
        if (hash == 136844)return 496;
        if (hash == 57260)return 497;
        if (hash == 110230)return 498;
        if (hash == 164248)return 499;
        if (hash == 77748)return 500;
        if (hash == 82362)return 501;
        if (hash == 94797)return 502;
        if (hash == 81430)return 503;
        if (hash == 39432)return 504;
        if (hash == 127456)return 505;
        if (hash == 47276)return 506;
        if (hash == 153848)return 507;
        if (hash == 55027)return 508;
        if (hash == 170546)return 509;
        if (hash == 182473)return 510;
        if (hash == 11015)return 511;
        if (hash == 174882)return 512;
        if (hash == 55875)return 513;
        if (hash == 6190)return 514;
        if (hash == 21995)return 515;
        if (hash == 195344)return 516;
        if (hash == 79534)return 517;
        if (hash == 132860)return 518;
        if (hash == 23498)return 519;
        if (hash == 200168)return 520;
        if (hash == 169968)return 521;
        if (hash == 192838)return 522;
        if (hash == 19729)return 523;
        if (hash == 100971)return 524;
        if (hash == 70131)return 525;
        if (hash == 133900)return 526;
        if (hash == 150991)return 527;
        if (hash == 75537)return 528;
        if (hash == 67473)return 529;
        if (hash == 176760)return 530;
        if (hash == 32523)return 531;
        if (hash == 186045)return 532;
        if (hash == 18203)return 533;
        if (hash == 2699)return 534;
        if (hash == 56904)return 535;
        if (hash == 125270)return 536;
        if (hash == 6642)return 537;
        if (hash == 82369)return 538;
        if (hash == 160090)return 539;
        if (hash == 130382)return 540;
        if (hash == 185582)return 541;
        if (hash == 66414)return 542;
        if (hash == 129107)return 543;
        if (hash == 184936)return 544;
        if (hash == 18832)return 545;
        if (hash == 48267)return 546;
        if (hash == 37057)return 547;
        if (hash == 45761)return 548;
        if (hash == 106734)return 549;
        if (hash == 129228)return 550;
        if (hash == 162643)return 551;
        if (hash == 173161)return 552;
        if (hash == 152710)return 553;
        if (hash == 10424)return 554;
        if (hash == 29642)return 555;
        if (hash == 137851)return 556;
        if (hash == 87795)return 557;
        if (hash == 33182)return 558;
        if (hash == 110924)return 559;
        if (hash == 528)return 560;
        if (hash == 151714)return 561;
        if (hash == 14581)return 562;
        if (hash == 128225)return 563;
        if (hash == 37033)return 564;
        if (hash == 148475)return 565;
        if (hash == 57917)return 566;
        if (hash == 109399)return 567;
        if (hash == 184626)return 568;
        if (hash == 125133)return 569;
        if (hash == 171773)return 570;
        if (hash == 162170)return 571;
        if (hash == 157622)return 572;
        if (hash == 64232)return 573;
        if (hash == 12427)return 574;
        if (hash == 12181)return 575;
        if (hash == 134352)return 576;
        if (hash == 142382)return 577;
        if (hash == 24700)return 578;
        if (hash == 131076)return 579;
        if (hash == 115980)return 580;
        if (hash == 129080)return 581;
        if (hash == 36126)return 582;
        if (hash == 39158)return 583;
        if (hash == 80915)return 584;
        if (hash == 181038)return 585;
        if (hash == 59641)return 586;
        if (hash == 27059)return 587;
        if (hash == 48236)return 588;
        if (hash == 192423)return 589;
        if (hash == 94548)return 590;
        if (hash == 86059)return 591;
        if (hash == 177724)return 592;
        if (hash == 64948)return 593;
        if (hash == 202096)return 594;
        if (hash == 30188)return 595;
        if (hash == 158966)return 596;
        if (hash == 121820)return 597;
        if (hash == 43210)return 598;
        if (hash == 122902)return 599;
        if (hash == 4723)return 600;
        if (hash == 193878)return 601;
        if (hash == 162704)return 602;
        if (hash == 68938)return 603;
        if (hash == 175244)return 604;
        if (hash == 160214)return 605;
        if (hash == 92746)return 606;
        if (hash == 65036)return 607;
        if (hash == 34868)return 608;
        if (hash == 122234)return 609;
        if (hash == 13876)return 610;
        if (hash == 4857)return 611;
        if (hash == 25770)return 612;
        if (hash == 202249)return 613;
        if (hash == 114564)return 614;
        if (hash == 149916)return 615;
        if (hash == 112988)return 616;
        if (hash == 113174)return 617;
        if (hash == 42921)return 618;
        if (hash == 33243)return 619;
        if (hash == 29139)return 620;
        if (hash == 198589)return 621;
        if (hash == 78531)return 622;
        if (hash == 142116)return 623;
        if (hash == 184920)return 624;
        if (hash == 102642)return 625;
        if (hash == 66012)return 626;
        if (hash == 178694)return 627;
        if (hash == 202089)return 628;
        if (hash == 91886)return 629;
        if (hash == 51561)return 630;
        if (hash == 67475)return 631;
        if (hash == 105730)return 632;
        if (hash == 104323)return 633;
        if (hash == 181203)return 634;
        if (hash == 8074)return 635;
        if (hash == 147593)return 636;
        if (hash == 197962)return 637;
        if (hash == 187383)return 638;
        if (hash == 8421)return 639;
        if (hash == 27708)return 640;
        if (hash == 88062)return 641;
        if (hash == 115963)return 642;
        if (hash == 19882)return 643;
        if (hash == 82090)return 644;
        if (hash == 29226)return 645;
        if (hash == 140140)return 646;
        if (hash == 183232)return 647;
        if (hash == 51797)return 648;
        if (hash == 197253)return 649;
        if (hash == 201830)return 650;
        if (hash == 131136)return 651;
        if (hash == 50628)return 652;
        if (hash == 40925)return 653;
        if (hash == 119139)return 654;
        if (hash == 48896)return 655;
        if (hash == 44485)return 656;
        if (hash == 4283)return 657;
        if (hash == 3023)return 658;
        if (hash == 18879)return 659;
        if (hash == 185882)return 660;
        if (hash == 171170)return 661;
        if (hash == 202657)return 662;
        if (hash == 81924)return 663;
        if (hash == 86266)return 664;
        if (hash == 6915)return 665;
        if (hash == 136906)return 666;
        if (hash == 102159)return 667;
        if (hash == 7745)return 668;
        if (hash == 179795)return 669;
        if (hash == 200476)return 670;
        if (hash == 70829)return 671;
        if (hash == 70809)return 672;
        if (hash == 165207)return 673;
        if (hash == 199603)return 674;
        if (hash == 78598)return 675;
        if (hash == 78597)return 676;
        if (hash == 10667)return 677;
        if (hash == 82612)return 678;
        if (hash == 102591)return 679;
        if (hash == 177423)return 680;
        if (hash == 116832)return 681;
        if (hash == 124818)return 682;
        if (hash == 79526)return 683;
        if (hash == 6123)return 684;
        if (hash == 72457)return 685;
        if (hash == 68773)return 686;
        if (hash == 27131)return 687;
        if (hash == 124568)return 688;
        if (hash == 124655)return 689;
        if (hash == 95559)return 690;
        if (hash == 159885)return 691;
        if (hash == 53521)return 692;
        if (hash == 6886)return 693;
        if (hash == 125188)return 694;
        if (hash == 31061)return 695;
        if (hash == 27300)return 696;
        if (hash == 66014)return 697;
        if (hash == 111295)return 698;
        if (hash == 140049)return 699;
        if (hash == 173858)return 700;
        if (hash == 22148)return 701;
        if (hash == 179684)return 702;
        if (hash == 164628)return 703;
        if (hash == 36988)return 704;
        if (hash == 143294)return 705;
        if (hash == 6559)return 706;
        if (hash == 145674)return 707;
        if (hash == 96164)return 708;
        if (hash == 22387)return 709;
        if (hash == 16075)return 710;
        if (hash == 143233)return 711;
        if (hash == 119973)return 712;
        if (hash == 158180)return 713;
        if (hash == 15925)return 714;
        if (hash == 167169)return 715;
        if (hash == 13474)return 716;
        if (hash == 126001)return 717;
        if (hash == 20770)return 718;
        if (hash == 152721)return 719;
        if (hash == 122561)return 720;
        if (hash == 40479)return 721;
        if (hash == 77256)return 722;
        if (hash == 148821)return 723;
        if (hash == 201427)return 724;
        if (hash == 168716)return 725;
        if (hash == 116347)return 726;
        if (hash == 91760)return 727;
        if (hash == 65546)return 728;
        if (hash == 184755)return 729;
        if (hash == 28723)return 730;
        if (hash == 93866)return 731;
        if (hash == 12597)return 732;
        if (hash == 170387)return 733;
        if (hash == 67564)return 734;
        if (hash == 86548)return 735;
        if (hash == 99687)return 736;
        if (hash == 55994)return 737;
        if (hash == 43627)return 738;
        if (hash == 163261)return 739;
        if (hash == 8939)return 740;
        if (hash == 141057)return 741;
        if (hash == 173993)return 742;
        if (hash == 182171)return 743;
        if (hash == 156694)return 744;
        if (hash == 80688)return 745;
        if (hash == 41228)return 746;
        if (hash == 26132)return 747;
        if (hash == 32739)return 748;
        if (hash == 157785)return 749;
        if (hash == 100641)return 750;
        if (hash == 70416)return 751;
        if (hash == 183188)return 752;
        if (hash == 110782)return 753;
        if (hash == 5394)return 754;
        if (hash == 96674)return 755;
        if (hash == 80290)return 756;
        if (hash == 79909)return 757;
        if (hash == 42012)return 758;
        if (hash == 201000)return 759;
        if (hash == 162145)return 760;
        if (hash == 129316)return 761;
        if (hash == 170696)return 762;
        if (hash == 135930)return 763;
        if (hash == 128475)return 764;
        if (hash == 168297)return 765;
        if (hash == 5256)return 766;
        if (hash == 194005)return 767;
        if (hash == 161521)return 768;
        if (hash == 48690)return 769;
        if (hash == 110578)return 770;
        if (hash == 110576)return 771;
        if (hash == 194809)return 772;
        if (hash == 12673)return 773;
        if (hash == 17517)return 774;
        if (hash == 33779)return 775;
        if (hash == 150748)return 776;
        if (hash == 86828)return 777;
        if (hash == 50775)return 778;
        if (hash == 50730)return 779;
        if (hash == 158942)return 780;
        if (hash == 101764)return 781;
        if (hash == 94665)return 782;
        if (hash == 134230)return 783;
        if (hash == 73802)return 784;
        if (hash == 83404)return 785;
        if (hash == 18790)return 786;
        if (hash == 39764)return 787;
        if (hash == 55562)return 788;
        if (hash == 2974)return 789;
        if (hash == 121086)return 790;
        if (hash == 53662)return 791;
        if (hash == 61734)return 792;
        if (hash == 54486)return 793;
        if (hash == 163027)return 794;
        if (hash == 118923)return 795;
        if (hash == 138833)return 796;
        if (hash == 75549)return 797;
        if (hash == 164252)return 798;
        if (hash == 101130)return 799;
        if (hash == 90306)return 800;
        if (hash == 45926)return 801;
        if (hash == 30220)return 802;
        if (hash == 19242)return 803;
        if (hash == 40335)return 804;
        if (hash == 146711)return 805;
        if (hash == 25849)return 806;
        if (hash == 158043)return 807;
        if (hash == 142072)return 808;
        if (hash == 140160)return 809;
        if (hash == 138415)return 810;
        if (hash == 94056)return 811;
        if (hash == 47632)return 812;
        if (hash == 71507)return 813;
        if (hash == 32531)return 814;
        if (hash == 131781)return 815;
        if (hash == 49260)return 816;
        if (hash == 79459)return 817;
        if (hash == 11929)return 818;
        if (hash == 27765)return 819;
        if (hash == 119227)return 820;
        if (hash == 28655)return 821;
        if (hash == 202693)return 822;
        if (hash == 12755)return 823;
        if (hash == 173138)return 824;
        if (hash == 125498)return 825;
        if (hash == 169521)return 826;
        if (hash == 103269)return 827;
        if (hash == 8175)return 828;
        if (hash == 12731)return 829;
        if (hash == 171692)return 830;
        if (hash == 20704)return 831;
        if (hash == 12424)return 832;
        if (hash == 58902)return 833;
        if (hash == 58890)return 834;
        if (hash == 43851)return 835;
        if (hash == 7435)return 836;
        if (hash == 109200)return 837;
        if (hash == 43802)return 838;
        if (hash == 187669)return 839;
        if (hash == 148111)return 840;
        if (hash == 163917)return 841;
        if (hash == 158872)return 842;
        if (hash == 148866)return 843;
        if (hash == 88466)return 844;
        if (hash == 28046)return 845;
        if (hash == 180963)return 846;
        if (hash == 164191)return 847;
        if (hash == 33043)return 848;
        if (hash == 52885)return 849;
        if (hash == 175656)return 850;
        if (hash == 118459)return 851;
        if (hash == 67984)return 852;
        if (hash == 104507)return 853;
        if (hash == 177472)return 854;
        if (hash == 156186)return 855;
        if (hash == 154908)return 856;
        if (hash == 184138)return 857;
        if (hash == 184079)return 858;
        if (hash == 172681)return 859;
        if (hash == 10936)return 860;
        if (hash == 200120)return 861;
        if (hash == 11638)return 862;
        if (hash == 137895)return 863;
        if (hash == 153939)return 864;
        if (hash == 131702)return 865;
        if (hash == 101324)return 866;
        if (hash == 200121)return 867;
        if (hash == 194689)return 868;
        if (hash == 110237)return 869;
        if (hash == 173860)return 870;
        if (hash == 127511)return 871;
        if (hash == 14942)return 872;
        if (hash == 103928)return 873;
        if (hash == 161142)return 874;
        if (hash == 143768)return 875;
        if (hash == 17036)return 876;
        if (hash == 120213)return 877;
        if (hash == 133821)return 878;
        if (hash == 146641)return 879;
        if (hash == 83900)return 880;
        if (hash == 197585)return 881;
        if (hash == 1335)return 882;
        if (hash == 69735)return 883;
        if (hash == 195635)return 884;
        if (hash == 193014)return 885;
        if (hash == 100838)return 886;
        if (hash == 31300)return 887;
        if (hash == 563)return 888;
        if (hash == 49854)return 889;
        if (hash == 188682)return 890;
        if (hash == 88716)return 891;
        if (hash == 196794)return 892;
        if (hash == 133651)return 893;
        if (hash == 83858)return 894;
        if (hash == 42004)return 895;
        if (hash == 106541)return 896;
        if (hash == 29081)return 897;
        if (hash == 55715)return 898;
        if (hash == 184525)return 899;
        if (hash == 179224)return 900;
        if (hash == 28775)return 901;
        if (hash == 105847)return 902;
        if (hash == 177918)return 903;
        if (hash == 85279)return 904;
        if (hash == 119359)return 905;
        if (hash == 6107)return 906;
        if (hash == 106392)return 907;
        if (hash == 75586)return 908;
        if (hash == 42412)return 909;
        if (hash == 80023)return 910;
        if (hash == 190689)return 911;
        if (hash == 61122)return 912;
        if (hash == 149388)return 913;
        if (hash == 177319)return 914;
        if (hash == 191376)return 915;
        if (hash == 453)return 916;
        if (hash == 192315)return 917;
        if (hash == 135582)return 918;
        if (hash == 146989)return 919;
        if (hash == 131897)return 920;
        if (hash == 41364)return 921;
        if (hash == 88540)return 922;
        if (hash == 6152)return 923;
        if (hash == 178091)return 924;
        if (hash == 72577)return 925;
        if (hash == 95339)return 926;
        if (hash == 163739)return 927;
        if (hash == 91615)return 928;
        if (hash == 164051)return 929;
        if (hash == 127827)return 930;
        if (hash == 117614)return 931;
        if (hash == 6328)return 932;
        if (hash == 28053)return 933;
        if (hash == 177860)return 934;
        if (hash == 32376)return 935;
        if (hash == 50169)return 936;
        if (hash == 198636)return 937;
        if (hash == 168445)return 938;
        if (hash == 75188)return 939;
        if (hash == 16722)return 940;
        if (hash == 161135)return 941;
        if (hash == 200318)return 942;
        if (hash == 51052)return 943;
        if (hash == 36869)return 944;
        if (hash == 33189)return 945;
        if (hash == 38307)return 946;
        if (hash == 7051)return 947;
        if (hash == 125936)return 948;
        if (hash == 93262)return 949;
        if (hash == 147806)return 950;
        if (hash == 40411)return 951;
        if (hash == 180532)return 952;
        if (hash == 183131)return 953;
        if (hash == 106594)return 954;
        if (hash == 45131)return 955;
        if (hash == 30015)return 956;
        if (hash == 78434)return 957;
        if (hash == 128472)return 958;
        if (hash == 145154)return 959;
        if (hash == 178849)return 960;
        if (hash == 163753)return 961;
        if (hash == 101545)return 962;
        if (hash == 11244)return 963;
        if (hash == 144823)return 964;
        if (hash == 74763)return 965;
        if (hash == 164041)return 966;
        if (hash == 146339)return 967;
        if (hash == 82691)return 968;
        if (hash == 111512)return 969;
        if (hash == 105651)return 970;
        if (hash == 57820)return 971;
        if (hash == 193049)return 972;
        if (hash == 164461)return 973;
        if (hash == 93359)return 974;
        if (hash == 187605)return 975;
        if (hash == 126506)return 976;
        if (hash == 15157)return 977;
        if (hash == 24948)return 978;
        if (hash == 122808)return 979;
        if (hash == 19691)return 980;
        if (hash == 163567)return 981;
        if (hash == 55006)return 982;
        if (hash == 18784)return 983;
        if (hash == 121402)return 984;
        if (hash == 121385)return 985;
        if (hash == 77702)return 986;
        if (hash == 89238)return 987;
        if (hash == 116804)return 988;
        if (hash == 172264)return 989;
        if (hash == 10950)return 990;
        if (hash == 109526)return 991;
        if (hash == 36941)return 992;
        if (hash == 95457)return 993;
        if (hash == 118575)return 994;
        if (hash == 81323)return 995;
        if (hash == 83328)return 996;
        if (hash == 197022)return 997;
        if (hash == 62595)return 998;
        if (hash == 166809)return 999;
        if (hash == 150923)return 1000;
        if (hash == 37952)return 1001;
        if (hash == 151760)return 1002;
        if (hash == 91325)return 1003;
        if (hash == 146962)return 1004;
        if (hash == 110840)return 1005;
        if (hash == 12635)return 1006;
        if (hash == 44841)return 1007;
        if (hash == 14691)return 1008;
        if (hash == 143757)return 1009;
        if (hash == 162089)return 1010;
        if (hash == 164305)return 1011;
        if (hash == 173002)return 1012;
        if (hash == 98135)return 1013;
        if (hash == 203496)return 1014;
        if (hash == 50828)return 1015;
        if (hash == 38700)return 1016;
        if (hash == 197623)return 1017;
        if (hash == 167438)return 1018;
        if (hash == 61804)return 1019;
        if (hash == 26621)return 1020;
        if (hash == 61770)return 1021;
        if (hash == 54441)return 1022;
        if (hash == 32257)return 1023;
        if (hash == 17207)return 1024;
        if (hash == 130866)return 1025;
        if (hash == 37113)return 1026;
        if (hash == 18120)return 1027;
        if (hash == 3022)return 1028;
        if (hash == 131782)return 1029;
        if (hash == 132455)return 1030;
        if (hash == 95156)return 1031;
        if (hash == 163596)return 1032;
        if (hash == 126297)return 1033;
        if (hash == 120588)return 1034;
        if (hash == 130833)return 1035;
        if (hash == 105512)return 1036;
        if (hash == 907)return 1037;
        if (hash == 104248)return 1038;
        if (hash == 29495)return 1039;
        if (hash == 14379)return 1040;
        if (hash == 98067)return 1041;
        if (hash == 199648)return 1042;
        if (hash == 98059)return 1043;
        if (hash == 71683)return 1044;
        if (hash == 166425)return 1045;
        if (hash == 7901)return 1046;
        if (hash == 114277)return 1047;
        if (hash == 99181)return 1048;
        if (hash == 60728)return 1049;
        if (hash == 144562)return 1050;
        if (hash == 130703)return 1051;
        if (hash == 197674)return 1052;
        if (hash == 191772)return 1053;
        if (hash == 94233)return 1054;
        if (hash == 117925)return 1055;
        if (hash == 91299)return 1056;
        if (hash == 79403)return 1057;
        if (hash == 61395)return 1058;
        if (hash == 116313)return 1059;
        if (hash == 8478)return 1060;
        if (hash == 181403)return 1061;
        if (hash == 8731)return 1062;
        if (hash == 178720)return 1063;
        if (hash == 64858)return 1064;
        if (hash == 12526)return 1065;
        if (hash == 20238)return 1066;
        if (hash == 202271)return 1067;
        if (hash == 156977)return 1068;
        if (hash == 141885)return 1069;
        if (hash == 21158)return 1070;
        if (hash == 141222)return 1071;
        if (hash == 117850)return 1072;
        if (hash == 186673)return 1073;
        if (hash == 149305)return 1074;
        if (hash == 171786)return 1075;
        if (hash == 86618)return 1076;
        if (hash == 77602)return 1077;
        if (hash == 42240)return 1078;
        if (hash == 179011)return 1079;
        if (hash == 31529)return 1080;
        if (hash == 202388)return 1081;
        if (hash == 130110)return 1082;
        if (hash == 108617)return 1083;
        if (hash == 154775)return 1084;
        if (hash == 113417)return 1085;
        if (hash == 104006)return 1086;
        if (hash == 73805)return 1087;
        if (hash == 191427)return 1088;
        if (hash == 203508)return 1089;
        if (hash == 173324)return 1090;
        if (hash == 12611)return 1091;
        if (hash == 174258)return 1092;
        if (hash == 96252)return 1093;
        if (hash == 142425)return 1094;
        if (hash == 158481)return 1095;
        if (hash == 148364)return 1096;
        if (hash == 77691)return 1097;
        if (hash == 79853)return 1098;
        if (hash == 95608)return 1099;
        if (hash == 13888)return 1100;
        if (hash == 100419)return 1101;
        if (hash == 110747)return 1102;
        if (hash == 14670)return 1103;
        if (hash == 101054)return 1104;
        if (hash == 136333)return 1105;
        if (hash == 158258)return 1106;
        if (hash == 67684)return 1107;
        if (hash == 12610)return 1108;
        if (hash == 12774)return 1109;
        if (hash == 1092)return 1110;
        if (hash == 164937)return 1111;
        if (hash == 86389)return 1112;
        if (hash == 155130)return 1113;
        if (hash == 171187)return 1114;
        if (hash == 125946)return 1115;
        if (hash == 153904)return 1116;
        if (hash == 130277)return 1117;
        if (hash == 141095)return 1118;
        if (hash == 72002)return 1119;
        if (hash == 54787)return 1120;
        if (hash == 11086)return 1121;
        if (hash == 129589)return 1122;
        if (hash == 20165)return 1123;
        if (hash == 110878)return 1124;
        if (hash == 186204)return 1125;
        if (hash == 50364)return 1126;
        if (hash == 14811)return 1127;
        if (hash == 6663)return 1128;
        if (hash == 107085)return 1129;
        if (hash == 76963)return 1130;
        if (hash == 15967)return 1131;
        if (hash == 82813)return 1132;
        if (hash == 16551)return 1133;
        if (hash == 129992)return 1134;
        if (hash == 196536)return 1135;
        if (hash == 123852)return 1136;
        if (hash == 192218)return 1137;
        if (hash == 94573)return 1138;
        if (hash == 10853)return 1139;
        if (hash == 105966)return 1140;
        if (hash == 151581)return 1141;
        if (hash == 102359)return 1142;
        if (hash == 27796)return 1143;
        if (hash == 158061)return 1144;
        if (hash == 62769)return 1145;
        if (hash == 125922)return 1146;
        if (hash == 61049)return 1147;
        if (hash == 77137)return 1148;
        if (hash == 197844)return 1149;
        if (hash == 71389)return 1150;
        if (hash == 61760)return 1151;
        if (hash == 18776)return 1152;
        if (hash == 174834)return 1153;
        if (hash == 195356)return 1154;
        if (hash == 99521)return 1155;
        if (hash == 11952)return 1156;
        if (hash == 58350)return 1157;
        if (hash == 26222)return 1158;
        if (hash == 127626)return 1159;
        if (hash == 19642)return 1160;
        if (hash == 91249)return 1161;
        if (hash == 132869)return 1162;
        if (hash == 164376)return 1163;
        if (hash == 157072)return 1164;
        if (hash == 166004)return 1165;
        if (hash == 120676)return 1166;
        if (hash == 30119)return 1167;
        if (hash == 81576)return 1168;
        if (hash == 146085)return 1169;
        if (hash == 47912)return 1170;
        if (hash == 131469)return 1171;
        if (hash == 67729)return 1172;
        if (hash == 192167)return 1173;
        if (hash == 79196)return 1174;
        if (hash == 89221)return 1175;
        if (hash == 186194)return 1176;
        if (hash == 116649)return 1177;
        if (hash == 45918)return 1178;
        if (hash == 124228)return 1179;
        if (hash == 75222)return 1180;
        if (hash == 165761)return 1181;
        if (hash == 16839)return 1182;
        if (hash == 145629)return 1183;
        if (hash == 4516)return 1184;
        if (hash == 78720)return 1185;
        if (hash == 176307)return 1186;
        if (hash == 69349)return 1187;
        if (hash == 9825)return 1188;
        if (hash == 123059)return 1189;
        if (hash == 71252)return 1190;
        if (hash == 139610)return 1191;
        if (hash == 108655)return 1192;
        if (hash == 183544)return 1193;
        if (hash == 125595)return 1194;
        if (hash == 185627)return 1195;
        if (hash == 125271)return 1196;
        if (hash == 14100)return 1197;
        if (hash == 144442)return 1198;
        if (hash == 130976)return 1199;
        if (hash == 81144)return 1200;
        if (hash == 190176)return 1201;
        if (hash == 18713)return 1202;
        if (hash == 45191)return 1203;
        if (hash == 118449)return 1204;
        if (hash == 124952)return 1205;
        if (hash == 46611)return 1206;
        if (hash == 2947)return 1207;
        if (hash == 109557)return 1208;
        if (hash == 147672)return 1209;
        if (hash == 158903)return 1210;
        if (hash == 42324)return 1211;
        if (hash == 62003)return 1212;
        if (hash == 177323)return 1213;
        if (hash == 19230)return 1214;
        if (hash == 12829)return 1215;
        if (hash == 105762)return 1216;
        if (hash == 183800)return 1217;
        if (hash == 163625)return 1218;
        if (hash == 37350)return 1219;
        if (hash == 118344)return 1220;
        if (hash == 103249)return 1221;
        if (hash == 47512)return 1222;
        if (hash == 156345)return 1223;
        if (hash == 80852)return 1224;
        if (hash == 99980)return 1225;
        if (hash == 65764)return 1226;
        if (hash == 50619)return 1227;
        if (hash == 167088)return 1228;
        if (hash == 194537)return 1229;
        if (hash == 164500)return 1230;
        if (hash == 166540)return 1231;
        if (hash == 127031)return 1232;
        if (hash == 180354)return 1233;
        if (hash == 117449)return 1234;
        if (hash == 47263)return 1235;
        if (hash == 14257)return 1236;
        if (hash == 158136)return 1237;
        if (hash == 143774)return 1238;
        if (hash == 34069)return 1239;
        if (hash == 83379)return 1240;
        if (hash == 143431)return 1241;
        if (hash == 139237)return 1242;
        if (hash == 68274)return 1243;
        if (hash == 22972)return 1244;
        if (hash == 803)return 1245;
        if (hash == 189944)return 1246;
        if (hash == 174877)return 1247;
        if (hash == 144650)return 1248;
        if (hash == 187777)return 1249;
        if (hash == 28616)return 1250;
        if (hash == 103994)return 1251;
        if (hash == 133569)return 1252;
        if (hash == 93888)return 1253;
        if (hash == 30582)return 1254;
        if (hash == 42883)return 1255;
        if (hash == 18039)return 1256;
        if (hash == 10864)return 1257;
        if (hash == 92452)return 1258;
        if (hash == 43824)return 1259;
        if (hash == 21561)return 1260;
        if (hash == 181991)return 1261;
        if (hash == 86953)return 1262;
        if (hash == 184116)return 1263;
        if (hash == 153474)return 1264;
        if (hash == 154451)return 1265;
        if (hash == 175709)return 1266;
        if (hash == 150910)return 1267;
        if (hash == 141531)return 1268;
        if (hash == 74546)return 1269;
        if (hash == 153408)return 1270;
        if (hash == 11699)return 1271;
        if (hash == 127408)return 1272;
        if (hash == 69158)return 1273;
        if (hash == 40167)return 1274;
        if (hash == 92991)return 1275;
        if (hash == 86178)return 1276;
        if (hash == 203760)return 1277;
        if (hash == 53403)return 1278;
        if (hash == 25328)return 1279;
        if (hash == 124560)return 1280;
        if (hash == 135048)return 1281;
        if (hash == 191963)return 1282;
        if (hash == 65387)return 1283;
        if (hash == 92158)return 1284;
        if (hash == 108159)return 1285;
        if (hash == 85975)return 1286;
        if (hash == 57116)return 1287;
        if (hash == 8103)return 1288;
        if (hash == 50975)return 1289;
        if (hash == 96327)return 1290;
        if (hash == 174352)return 1291;
        if (hash == 19517)return 1292;
        if (hash == 6761)return 1293;
        if (hash == 149084)return 1294;
        if (hash == 22454)return 1295;
        if (hash == 38309)return 1296;
        if (hash == 62138)return 1297;
        if (hash == 57608)return 1298;
        if (hash == 108320)return 1299;
        if (hash == 49544)return 1300;
        if (hash == 150008)return 1301;
        if (hash == 144889)return 1302;
        if (hash == 193707)return 1303;
        if (hash == 93946)return 1304;
        if (hash == 93938)return 1305;
        if (hash == 203547)return 1306;
        if (hash == 93921)return 1307;
        if (hash == 96086)return 1308;
        if (hash == 186980)return 1309;
        if (hash == 21924)return 1310;
        if (hash == 191865)return 1311;
        if (hash == 82146)return 1312;
        if (hash == 35126)return 1313;
        if (hash == 94563)return 1314;
        if (hash == 197412)return 1315;
        if (hash == 76647)return 1316;
        if (hash == 184136)return 1317;
        if (hash == 94948)return 1318;
        if (hash == 24361)return 1319;
        if (hash == 26910)return 1320;
        if (hash == 160511)return 1321;
        if (hash == 20060)return 1322;
        if (hash == 85037)return 1323;
        if (hash == 196164)return 1324;
        if (hash == 143483)return 1325;
        if (hash == 84390)return 1326;
        if (hash == 100488)return 1327;
        if (hash == 169710)return 1328;
        if (hash == 88282)return 1329;
        if (hash == 123357)return 1330;
        if (hash == 192619)return 1331;
        if (hash == 161421)return 1332;
        if (hash == 40103)return 1333;
        if (hash == 154292)return 1334;
        if (hash == 186992)return 1335;
        if (hash == 135314)return 1336;
        if (hash == 4102)return 1337;
        if (hash == 126568)return 1338;
        if (hash == 104354)return 1339;
        if (hash == 105283)return 1340;
        if (hash == 144189)return 1341;
        if (hash == 21165)return 1342;
        if (hash == 15805)return 1343;
        if (hash == 85488)return 1344;
        if (hash == 203090)return 1345;
        if (hash == 138338)return 1346;
        if (hash == 109769)return 1347;
        if (hash == 26463)return 1348;
        if (hash == 173312)return 1349;
        if (hash == 83212)return 1350;
        if (hash == 99130)return 1351;
        if (hash == 108791)return 1352;
        if (hash == 76814)return 1353;
        if (hash == 44591)return 1354;
        if (hash == 65084)return 1355;
        if (hash == 143097)return 1356;
        if (hash == 170267)return 1357;
        if (hash == 77829)return 1358;
        if (hash == 39128)return 1359;
        if (hash == 54958)return 1360;
        if (hash == 36672)return 1361;
        if (hash == 185512)return 1362;
        if (hash == 164005)return 1363;
        if (hash == 148932)return 1364;
        if (hash == 11551)return 1365;
        if (hash == 133830)return 1366;
        if (hash == 26125)return 1367;
        if (hash == 90100)return 1368;
        if (hash == 39311)return 1369;
        if (hash == 89434)return 1370;
        if (hash == 169729)return 1371;
        if (hash == 27666)return 1372;
        if (hash == 117737)return 1373;
        if (hash == 103305)return 1374;
        if (hash == 26158)return 1375;
        if (hash == 190990)return 1376;
        if (hash == 141613)return 1377;
        if (hash == 56022)return 1378;
        if (hash == 178427)return 1379;
        if (hash == 103070)return 1380;
        if (hash == 135806)return 1381;
        if (hash == 27884)return 1382;
        if (hash == 163345)return 1383;
        if (hash == 126032)return 1384;
        if (hash == 63939)return 1385;
        if (hash == 173012)return 1386;
        if (hash == 110916)return 1387;
        if (hash == 184163)return 1388;
        if (hash == 58468)return 1389;
        if (hash == 28266)return 1390;
        if (hash == 159643)return 1391;
        if (hash == 94967)return 1392;
        if (hash == 156043)return 1393;
        if (hash == 155601)return 1394;
        if (hash == 45777)return 1395;
        if (hash == 170464)return 1396;
        if (hash == 192854)return 1397;
        if (hash == 7284)return 1398;
        if (hash == 27961)return 1399;
        if (hash == 168532)return 1400;
        if (hash == 179058)return 1401;
        if (hash == 171708)return 1402;
        if (hash == 65344)return 1403;
        if (hash == 148812)return 1404;
        if (hash == 43874)return 1405;
        if (hash == 94871)return 1406;
        if (hash == 15363)return 1407;
        if (hash == 150135)return 1408;
        if (hash == 135033)return 1409;
        if (hash == 135028)return 1410;
        if (hash == 90663)return 1411;
        if (hash == 74048)return 1412;
        if (hash == 70373)return 1413;
        if (hash == 184032)return 1414;
        if (hash == 5869)return 1415;
        if (hash == 99225)return 1416;
        if (hash == 193204)return 1417;
        if (hash == 89359)return 1418;
        if (hash == 85054)return 1419;
        if (hash == 162345)return 1420;
        if (hash == 78673)return 1421;
        if (hash == 139576)return 1422;
        if (hash == 56474)return 1423;
        if (hash == 186666)return 1424;
        if (hash == 11182)return 1425;
        if (hash == 11162)return 1426;
        if (hash == 63373)return 1427;
        if (hash == 135255)return 1428;
        if (hash == 169764)return 1429;
        if (hash == 173013)return 1430;
        if (hash == 7396)return 1431;
        if (hash == 161760)return 1432;
        if (hash == 168367)return 1433;
        if (hash == 87595)return 1434;
        if (hash == 60723)return 1435;
        if (hash == 191892)return 1436;
        if (hash == 141577)return 1437;
        if (hash == 195595)return 1438;
        if (hash == 57689)return 1439;
        if (hash == 49200)return 1440;
        if (hash == 105803)return 1441;
        if (hash == 182189)return 1442;
        if (hash == 1753)return 1443;
        if (hash == 130539)return 1444;
        if (hash == 31122)return 1445;
        if (hash == 189989)return 1446;
        if (hash == 24651)return 1447;
        if (hash == 16571)return 1448;
        if (hash == 79550)return 1449;
        if (hash == 60634)return 1450;
        if (hash == 167010)return 1451;
        if (hash == 59966)return 1452;
        if (hash == 150773)return 1453;
        if (hash == 57905)return 1454;
        if (hash == 104074)return 1455;
        if (hash == 46199)return 1456;
        if (hash == 49416)return 1457;
        if (hash == 166902)return 1458;
        if (hash == 169421)return 1459;
        if (hash == 39802)return 1460;
        if (hash == 56010)return 1461;
        if (hash == 56679)return 1462;
        if (hash == 41151)return 1463;
        if (hash == 53323)return 1464;
        if (hash == 198798)return 1465;
        if (hash == 167811)return 1466;
        if (hash == 122994)return 1467;
        if (hash == 201142)return 1468;
        if (hash == 92422)return 1469;
        if (hash == 22625)return 1470;
        if (hash == 52089)return 1471;
        if (hash == 143784)return 1472;
        if (hash == 119522)return 1473;
        if (hash == 186931)return 1474;
        if (hash == 76496)return 1475;
        if (hash == 46310)return 1476;
        if (hash == 178173)return 1477;
        if (hash == 87615)return 1478;
        if (hash == 13742)return 1479;
        if (hash == 69393)return 1480;
        if (hash == 40781)return 1481;
        if (hash == 17051)return 1482;
        if (hash == 171837)return 1483;
        if (hash == 33060)return 1484;
        if (hash == 29320)return 1485;
        if (hash == 124633)return 1486;
        if (hash == 169667)return 1487;
        if (hash == 126646)return 1488;
        if (hash == 7504)return 1489;
        if (hash == 91623)return 1490;
        if (hash == 121555)return 1491;
        if (hash == 2641)return 1492;
        if (hash == 157932)return 1493;
        if (hash == 147783)return 1494;
        if (hash == 179829)return 1495;
        if (hash == 112943)return 1496;
        if (hash == 141234)return 1497;
        if (hash == 94848)return 1498;
        if (hash == 42258)return 1499;
        if (hash == 141583)return 1500;
        if (hash == 43708)return 1501;
        if (hash == 202161)return 1502;
        if (hash == 5194)return 1503;
        if (hash == 111577)return 1504;
        if (hash == 66249)return 1505;
        if (hash == 172513)return 1506;
        if (hash == 90084)return 1507;
        if (hash == 121189)return 1508;
        if (hash == 15521)return 1509;
        if (hash == 92563)return 1510;
        if (hash == 108382)return 1511;
        if (hash == 35418)return 1512;
        if (hash == 20347)return 1513;
        if (hash == 83877)return 1514;
        if (hash == 64184)return 1515;
        if (hash == 152967)return 1516;
        if (hash == 139938)return 1517;
        if (hash == 101694)return 1518;
        if (hash == 122122)return 1519;
        if (hash == 112006)return 1520;
        if (hash == 21442)return 1521;
        if (hash == 40361)return 1522;
        if (hash == 40804)return 1523;
        if (hash == 35577)return 1524;
        if (hash == 162898)return 1525;
        if (hash == 157291)return 1526;
        if (hash == 151810)return 1527;
        if (hash == 136693)return 1528;
        if (hash == 46131)return 1529;
        if (hash == 147196)return 1530;
        if (hash == 197282)return 1531;
        if (hash == 152942)return 1532;
        if (hash == 70192)return 1533;
        if (hash == 183870)return 1534;
        if (hash == 8747)return 1535;
        if (hash == 75655)return 1536;
        if (hash == 40859)return 1537;
        if (hash == 124376)return 1538;
        if (hash == 198412)return 1539;
        if (hash == 124375)return 1540;
        if (hash == 1362)return 1541;
        if (hash == 35390)return 1542;
        if (hash == 5232)return 1543;
        if (hash == 124043)return 1544;
        if (hash == 149756)return 1545;
        if (hash == 74273)return 1546;
        if (hash == 123348)return 1547;
        if (hash == 52814)return 1548;
        if (hash == 107728)return 1549;
        if (hash == 24092)return 1550;
        if (hash == 63028)return 1551;
        if (hash == 124121)return 1552;
        if (hash == 49523)return 1553;
        if (hash == 133040)return 1554;
        if (hash == 142665)return 1555;
        if (hash == 3589)return 1556;
        if (hash == 131409)return 1557;
        if (hash == 70698)return 1558;
        if (hash == 93787)return 1559;
        if (hash == 163887)return 1560;
        if (hash == 201686)return 1561;
        if (hash == 139464)return 1562;
        if (hash == 145781)return 1563;
        if (hash == 103722)return 1564;
        if (hash == 94128)return 1565;
        if (hash == 84852)return 1566;
        if (hash == 186325)return 1567;
        if (hash == 133924)return 1568;
        if (hash == 120624)return 1569;
        if (hash == 103752)return 1570;
        if (hash == 13197)return 1571;
        if (hash == 191128)return 1572;
        if (hash == 180219)return 1573;
        if (hash == 127664)return 1574;
        if (hash == 17465)return 1575;
        if (hash == 161384)return 1576;
        if (hash == 177380)return 1577;
        if (hash == 18989)return 1578;
        if (hash == 156757)return 1579;
        if (hash == 192729)return 1580;
        if (hash == 86084)return 1581;
        if (hash == 85777)return 1582;
        if (hash == 182917)return 1583;
        if (hash == 100044)return 1584;
        if (hash == 44487)return 1585;
        if (hash == 85456)return 1586;
        if (hash == 6727)return 1587;
        if (hash == 154108)return 1588;
        if (hash == 20434)return 1589;
        if (hash == 159698)return 1590;
        if (hash == 58056)return 1591;
        if (hash == 60963)return 1592;
        if (hash == 62542)return 1593;
        if (hash == 59508)return 1594;
        if (hash == 1504)return 1595;
        if (hash == 114232)return 1596;
        if (hash == 99136)return 1597;
        if (hash == 96986)return 1598;
        if (hash == 7944)return 1599;
        if (hash == 11797)return 1600;
        if (hash == 131867)return 1601;
        if (hash == 8823)return 1602;
        if (hash == 151842)return 1603;
        if (hash == 124621)return 1604;
        if (hash == 176527)return 1605;
        if (hash == 139288)return 1606;
        if (hash == 124134)return 1607;
        if (hash == 98631)return 1608;
        if (hash == 78840)return 1609;
        if (hash == 18449)return 1610;
        if (hash == 92160)return 1611;
        if (hash == 77321)return 1612;
        if (hash == 116660)return 1613;
        if (hash == 19307)return 1614;
        if (hash == 26042)return 1615;
        if (hash == 97067)return 1616;
        if (hash == 15193)return 1617;
        if (hash == 99423)return 1618;
        if (hash == 124815)return 1619;
        if (hash == 109719)return 1620;
        if (hash == 72056)return 1621;
        if (hash == 160519)return 1622;
        if (hash == 52356)return 1623;
        if (hash == 166052)return 1624;
        if (hash == 11176)return 1625;
        if (hash == 93580)return 1626;
        if (hash == 59549)return 1627;
        if (hash == 172802)return 1628;
        if (hash == 114026)return 1629;
        if (hash == 43353)return 1630;
        if (hash == 175195)return 1631;
        if (hash == 117668)return 1632;
        if (hash == 77995)return 1633;
        if (hash == 28144)return 1634;
        if (hash == 146647)return 1635;
        if (hash == 33992)return 1636;
        if (hash == 56222)return 1637;
        if (hash == 42047)return 1638;
        if (hash == 42039)return 1639;
        if (hash == 200962)return 1640;
        if (hash == 110405)return 1641;
        if (hash == 65092)return 1642;
        if (hash == 149292)return 1643;
        if (hash == 188868)return 1644;
        if (hash == 15598)return 1645;
        if (hash == 9449)return 1646;
        if (hash == 83850)return 1647;
        if (hash == 60601)return 1648;
        if (hash == 56880)return 1649;
        if (hash == 95788)return 1650;
        if (hash == 167380)return 1651;
        if (hash == 152273)return 1652;
        if (hash == 21939)return 1653;
        if (hash == 78253)return 1654;
        if (hash == 145320)return 1655;
        if (hash == 50470)return 1656;
        if (hash == 26715)return 1657;
        if (hash == 200795)return 1658;
        if (hash == 198760)return 1659;
        if (hash == 5512)return 1660;
        if (hash == 61477)return 1661;
        if (hash == 37312)return 1662;
        if (hash == 170468)return 1663;
        if (hash == 64104)return 1664;
        if (hash == 151919)return 1665;
        if (hash == 25652)return 1666;
        if (hash == 163489)return 1667;
        if (hash == 64560)return 1668;
        if (hash == 27080)return 1669;
        if (hash == 46936)return 1670;
        if (hash == 71427)return 1671;
        if (hash == 33946)return 1672;
        if (hash == 192897)return 1673;
        if (hash == 191089)return 1674;
        if (hash == 155633)return 1675;
        if (hash == 43637)return 1676;
        if (hash == 133457)return 1677;
        if (hash == 56282)return 1678;
        if (hash == 6028)return 1679;
        if (hash == 6740)return 1680;
        if (hash == 96857)return 1681;
        if (hash == 21369)return 1682;
        if (hash == 72366)return 1683;
        if (hash == 50118)return 1684;
        if (hash == 136471)return 1685;
        if (hash == 90637)return 1686;
        if (hash == 10479)return 1687;
        if (hash == 119590)return 1688;
        if (hash == 200074)return 1689;
        if (hash == 12113)return 1690;
        if (hash == 16860)return 1691;
        if (hash == 91060)return 1692;
        if (hash == 32058)return 1693;
        if (hash == 61648)return 1694;
        if (hash == 182378)return 1695;
        if (hash == 59340)return 1696;
        if (hash == 167282)return 1697;
        if (hash == 74971)return 1698;
        if (hash == 77630)return 1699;
        if (hash == 140502)return 1700;
        if (hash == 5868)return 1701;
        if (hash == 108842)return 1702;
        if (hash == 138136)return 1703;
        if (hash == 40261)return 1704;
        if (hash == 132667)return 1705;
        if (hash == 31772)return 1706;
        if (hash == 109773)return 1707;
        if (hash == 88396)return 1708;
        if (hash == 180807)return 1709;
        if (hash == 38513)return 1710;
        if (hash == 140130)return 1711;
        if (hash == 109898)return 1712;
        if (hash == 177487)return 1713;
        if (hash == 109327)return 1714;
        if (hash == 45735)return 1715;
        if (hash == 126148)return 1716;
        if (hash == 83619)return 1717;
        if (hash == 170859)return 1718;
        if (hash == 89919)return 1719;
        if (hash == 69483)return 1720;
        if (hash == 131505)return 1721;
        if (hash == 11671)return 1722;
        if (hash == 170407)return 1723;
        if (hash == 65535)return 1724;
        if (hash == 167314)return 1725;
        if (hash == 165196)return 1726;
        if (hash == 49077)return 1727;
        if (hash == 132829)return 1728;
        if (hash == 153536)return 1729;
        if (hash == 58123)return 1730;
        if (hash == 67041)return 1731;
        if (hash == 181231)return 1732;
        if (hash == 75285)return 1733;
        if (hash == 163925)return 1734;
        if (hash == 15977)return 1735;
        if (hash == 172249)return 1736;
        if (hash == 54865)return 1737;
        if (hash == 126903)return 1738;
        if (hash == 27715)return 1739;
        if (hash == 21552)return 1740;
        if (hash == 101204)return 1741;
        if (hash == 8167)return 1742;
        if (hash == 126670)return 1743;
        if (hash == 156114)return 1744;
        if (hash == 4685)return 1745;
        if (hash == 186962)return 1746;
        if (hash == 153938)return 1747;
        if (hash == 155757)return 1748;
        if (hash == 174063)return 1749;
        if (hash == 55932)return 1750;
        if (hash == 19569)return 1751;
        if (hash == 180141)return 1752;
        if (hash == 172237)return 1753;
        if (hash == 93717)return 1754;
        if (hash == 178784)return 1755;
        if (hash == 169649)return 1756;
        if (hash == 96110)return 1757;
        if (hash == 166616)return 1758;
        if (hash == 170343)return 1759;
        if (hash == 193479)return 1760;
        if (hash == 167453)return 1761;
        if (hash == 157140)return 1762;
        if (hash == 150990)return 1763;
        if (hash == 31823)return 1764;
        if (hash == 34999)return 1765;
        if (hash == 70991)return 1766;
        if (hash == 15345)return 1767;
        if (hash == 71874)return 1768;
        if (hash == 1676)return 1769;
        if (hash == 61034)return 1770;
        if (hash == 2268)return 1771;
        if (hash == 135836)return 1772;
        if (hash == 185614)return 1773;
        if (hash == 137544)return 1774;
        if (hash == 203343)return 1775;
        if (hash == 175599)return 1776;
        if (hash == 2212)return 1777;
        if (hash == 91496)return 1778;
        if (hash == 23517)return 1779;
        if (hash == 161712)return 1780;
        if (hash == 80786)return 1781;
        if (hash == 118008)return 1782;
        if (hash == 29052)return 1783;
        if (hash == 83041)return 1784;
        if (hash == 91032)return 1785;
        if (hash == 34395)return 1786;
        if (hash == 187751)return 1787;
        if (hash == 172070)return 1788;
        if (hash == 178677)return 1789;
        if (hash == 147322)return 1790;
        if (hash == 147320)return 1791;
        if (hash == 52024)return 1792;
        if (hash == 13404)return 1793;
        if (hash == 20611)return 1794;
        if (hash == 65295)return 1795;
        if (hash == 171616)return 1796;
        if (hash == 55655)return 1797;
        if (hash == 38469)return 1798;
        if (hash == 84484)return 1799;
        if (hash == 147090)return 1800;
        if (hash == 132020)return 1801;
        if (hash == 39890)return 1802;
        if (hash == 145266)return 1803;
        if (hash == 159690)return 1804;
        if (hash == 17814)return 1805;
        if (hash == 81507)return 1806;
        if (hash == 282)return 1807;
        if (hash == 89391)return 1808;
        if (hash == 148446)return 1809;
        if (hash == 60925)return 1810;
        if (hash == 49430)return 1811;
        if (hash == 78464)return 1812;
        if (hash == 142916)return 1813;
        if (hash == 110486)return 1814;
        if (hash == 124776)return 1815;
        if (hash == 81234)return 1816;
        if (hash == 58024)return 1817;
        if (hash == 149524)return 1818;
        if (hash == 43819)return 1819;
        if (hash == 48879)return 1820;
        if (hash == 97800)return 1821;
        if (hash == 91444)return 1822;
        if (hash == 124128)return 1823;
        if (hash == 8647)return 1824;
        if (hash == 77216)return 1825;
        if (hash == 2604)return 1826;
        if (hash == 19171)return 1827;
        if (hash == 153641)return 1828;
        if (hash == 32892)return 1829;
        if (hash == 32868)return 1830;
        if (hash == 94938)return 1831;
        if (hash == 162751)return 1832;
        if (hash == 31667)return 1833;
        if (hash == 200899)return 1834;
        if (hash == 23147)return 1835;
        if (hash == 47880)return 1836;
        if (hash == 156011)return 1837;
        if (hash == 78313)return 1838;
        if (hash == 40712)return 1839;
        if (hash == 69645)return 1840;
        if (hash == 46323)return 1841;
        if (hash == 142507)return 1842;
        if (hash == 48939)return 1843;
        if (hash == 105306)return 1844;
        if (hash == 20298)return 1845;
        if (hash == 39819)return 1846;
        if (hash == 32147)return 1847;
        if (hash == 130965)return 1848;
        if (hash == 5696)return 1849;
        if (hash == 47090)return 1850;
        if (hash == 198566)return 1851;
        if (hash == 102752)return 1852;
        if (hash == 54307)return 1853;
        if (hash == 72584)return 1854;
        if (hash == 2710)return 1855;
        if (hash == 38489)return 1856;
        if (hash == 133139)return 1857;
        if (hash == 73128)return 1858;
        if (hash == 111653)return 1859;
        if (hash == 104904)return 1860;
        if (hash == 165913)return 1861;
        if (hash == 21352)return 1862;
        if (hash == 170701)return 1863;
        if (hash == 146110)return 1864;
        if (hash == 108237)return 1865;
        if (hash == 173231)return 1866;
        if (hash == 148403)return 1867;
        if (hash == 162209)return 1868;
        if (hash == 23414)return 1869;
        if (hash == 156947)return 1870;
        if (hash == 43607)return 1871;
        if (hash == 21412)return 1872;
        if (hash == 88351)return 1873;
        if (hash == 108243)return 1874;
        if (hash == 38532)return 1875;
        if (hash == 179658)return 1876;
        if (hash == 197071)return 1877;
        if (hash == 91394)return 1878;
        if (hash == 151981)return 1879;
        if (hash == 127250)return 1880;
        if (hash == 101909)return 1881;
        if (hash == 197979)return 1882;
        if (hash == 127285)return 1883;
        if (hash == 69404)return 1884;
        if (hash == 89318)return 1885;
        if (hash == 197973)return 1886;
        if (hash == 197953)return 1887;
        if (hash == 107846)return 1888;
        if (hash == 182899)return 1889;
        if (hash == 134693)return 1890;
        if (hash == 137593)return 1891;
        if (hash == 137581)return 1892;
        if (hash == 24584)return 1893;
        if (hash == 3035)return 1894;
        if (hash == 192198)return 1895;
        if (hash == 82861)return 1896;
        if (hash == 141297)return 1897;
        if (hash == 203921)return 1898;
        if (hash == 42631)return 1899;
        if (hash == 186615)return 1900;
        if (hash == 197671)return 1901;
        if (hash == 98168)return 1902;
        if (hash == 90022)return 1903;
        if (hash == 132277)return 1904;
        if (hash == 68776)return 1905;
        if (hash == 123302)return 1906;
        if (hash == 29528)return 1907;
        if (hash == 162406)return 1908;
        if (hash == 50259)return 1909;
        if (hash == 157547)return 1910;
        if (hash == 52771)return 1911;
        if (hash == 185197)return 1912;
        if (hash == 196018)return 1913;
        if (hash == 183423)return 1914;
        if (hash == 138130)return 1915;
        if (hash == 46771)return 1916;
        if (hash == 169754)return 1917;
        if (hash == 199964)return 1918;
        if (hash == 151464)return 1919;
        if (hash == 519)return 1920;
        if (hash == 9438)return 1921;
        if (hash == 144637)return 1922;
        if (hash == 182074)return 1923;
        if (hash == 94098)return 1924;
        if (hash == 71243)return 1925;
        if (hash == 24811)return 1926;
        if (hash == 52932)return 1927;
        if (hash == 155454)return 1928;
        if (hash == 125277)return 1929;
        if (hash == 49759)return 1930;
        if (hash == 194190)return 1931;
        if (hash == 75875)return 1932;
        if (hash == 182251)return 1933;
        if (hash == 42673)return 1934;
        if (hash == 195264)return 1935;
        if (hash == 62925)return 1936;
        if (hash == 69532)return 1937;
        if (hash == 128198)return 1938;
        if (hash == 49175)return 1939;
        if (hash == 184078)return 1940;
        if (hash == 55630)return 1941;
        if (hash == 196175)return 1942;
        if (hash == 174652)return 1943;
        if (hash == 84813)return 1944;
        if (hash == 48413)return 1945;
        if (hash == 73352)return 1946;
        if (hash == 165536)return 1947;
        if (hash == 182810)return 1948;
        if (hash == 154081)return 1949;
        if (hash == 50656)return 1950;
        if (hash == 164060)return 1951;
        if (hash == 69619)return 1952;
        if (hash == 10843)return 1953;
        if (hash == 93747)return 1954;
        if (hash == 115347)return 1955;
        if (hash == 180015)return 1956;
        if (hash == 60171)return 1957;
        if (hash == 71424)return 1958;
        if (hash == 69539)return 1959;
        if (hash == 56331)return 1960;
        if (hash == 122265)return 1961;
        if (hash == 175377)return 1962;
        if (hash == 143634)return 1963;
        if (hash == 15527)return 1964;
        if (hash == 70237)return 1965;
        if (hash == 6807)return 1966;
        if (hash == 84179)return 1967;
        if (hash == 14107)return 1968;
        if (hash == 135807)return 1969;
        if (hash == 189787)return 1970;
        if (hash == 129426)return 1971;
        if (hash == 77030)return 1972;
        if (hash == 87279)return 1973;
        if (hash == 29701)return 1974;
        if (hash == 83671)return 1975;
        if (hash == 45107)return 1976;
        if (hash == 166312)return 1977;
        if (hash == 17382)return 1978;
        if (hash == 146434)return 1979;
        if (hash == 30427)return 1980;
        if (hash == 55869)return 1981;
        if (hash == 115494)return 1982;
        if (hash == 70256)return 1983;
        if (hash == 100999)return 1984;
        if (hash == 55816)return 1985;
        if (hash == 174563)return 1986;
        if (hash == 101701)return 1987;
        if (hash == 159211)return 1988;
        if (hash == 15604)return 1989;
        if (hash == 78693)return 1990;
        if (hash == 78648)return 1991;
        if (hash == 42315)return 1992;
        if (hash == 18273)return 1993;
        if (hash == 29148)return 1994;
        if (hash == 153988)return 1995;
        if (hash == 18192)return 1996;
        if (hash == 44914)return 1997;
        if (hash == 83912)return 1998;
        if (hash == 24790)return 1999;
        if (hash == 32580)return 2000;
        if (hash == 117916)return 2001;
        if (hash == 7418)return 2002;
        if (hash == 48617)return 2003;
        if (hash == 30958)return 2004;
        if (hash == 96967)return 2005;
        if (hash == 34193)return 2006;
        if (hash == 69339)return 2007;
        if (hash == 85135)return 2008;
        if (hash == 25808)return 2009;
        if (hash == 181656)return 2010;
        if (hash == 61750)return 2011;
        if (hash == 58894)return 2012;
        if (hash == 109121)return 2013;
        if (hash == 116581)return 2014;
        if (hash == 66575)return 2015;
        if (hash == 124603)return 2016;
        if (hash == 110447)return 2017;
        if (hash == 16867)return 2018;
        if (hash == 190441)return 2019;
        if (hash == 190927)return 2020;
        if (hash == 39977)return 2021;
        if (hash == 40683)return 2022;
        if (hash == 154361)return 2023;
        if (hash == 71785)return 2024;
        if (hash == 127778)return 2025;
        if (hash == 15018)return 2026;
        if (hash == 36517)return 2027;
        if (hash == 71947)return 2028;
        if (hash == 22933)return 2029;
        if (hash == 12315)return 2030;
        if (hash == 110152)return 2031;
        if (hash == 93039)return 2032;
        if (hash == 176780)return 2033;
        if (hash == 78905)return 2034;
        if (hash == 89884)return 2035;
        if (hash == 36980)return 2036;
        if (hash == 86098)return 2037;
        if (hash == 28525)return 2038;
        if (hash == 146334)return 2039;
        if (hash == 179034)return 2040;
        if (hash == 48477)return 2041;
        if (hash == 110648)return 2042;
        if (hash == 164644)return 2043;
        if (hash == 192742)return 2044;
        if (hash == 86896)return 2045;
        if (hash == 111304)return 2046;
        if (hash == 81072)return 2047;
        if (hash == 29874)return 2048;
        if (hash == 6879)return 2049;
        if (hash == 181538)return 2050;
        if (hash == 139056)return 2051;
        if (hash == 27018)return 2052;
        if (hash == 7919)return 2053;
        if (hash == 39120)return 2054;
        if (hash == 122601)return 2055;
        if (hash == 177414)return 2056;
        if (hash == 162440)return 2057;
        if (hash == 2270)return 2058;
        if (hash == 140358)return 2059;
        if (hash == 145349)return 2060;
        if (hash == 100352)return 2061;
        if (hash == 46539)return 2062;
        if (hash == 117017)return 2063;
        if (hash == 149025)return 2064;
        if (hash == 188839)return 2065;
        if (hash == 159395)return 2066;
        if (hash == 144274)return 2067;
        if (hash == 197719)return 2068;
        if (hash == 150510)return 2069;
        if (hash == 29759)return 2070;
        if (hash == 156500)return 2071;
        if (hash == 161651)return 2072;
        if (hash == 41658)return 2073;
        if (hash == 11478)return 2074;
        if (hash == 134046)return 2075;
        if (hash == 12667)return 2076;
        if (hash == 85866)return 2077;
        if (hash == 43002)return 2078;
        if (hash == 42201)return 2079;
        if (hash == 196449)return 2080;
        if (hash == 90385)return 2081;
        if (hash == 176619)return 2082;
        if (hash == 201349)return 2083;
        if (hash == 185938)return 2084;
        if (hash == 160828)return 2085;
        if (hash == 142054)return 2086;
        if (hash == 73461)return 2087;
        if (hash == 56697)return 2088;
        if (hash == 179298)return 2089;
        if (hash == 99362)return 2090;
        if (hash == 169218)return 2091;
        if (hash == 34695)return 2092;
        if (hash == 50735)return 2093;
        if (hash == 99293)return 2094;
        if (hash == 192390)return 2095;
        if (hash == 180682)return 2096;
        if (hash == 90347)return 2097;
        if (hash == 183645)return 2098;
        if (hash == 176820)return 2099;
        if (hash == 158597)return 2100;
        if (hash == 48134)return 2101;
        if (hash == 132303)return 2102;
        if (hash == 93656)return 2103;
        if (hash == 82677)return 2104;
        if (hash == 170458)return 2105;
        if (hash == 96817)return 2106;
        if (hash == 113172)return 2107;
        if (hash == 81297)return 2108;
        if (hash == 56299)return 2109;
        if (hash == 127510)return 2110;
        if (hash == 175823)return 2111;
        if (hash == 45278)return 2112;
        if (hash == 68010)return 2113;
        if (hash == 30706)return 2114;
        if (hash == 56324)return 2115;
        if (hash == 110305)return 2116;
        if (hash == 127041)return 2117;
        if (hash == 158570)return 2118;
        if (hash == 125691)return 2119;
        if (hash == 90659)return 2120;
        if (hash == 62483)return 2121;
        if (hash == 576)return 2122;
        if (hash == 53476)return 2123;
        if (hash == 120220)return 2124;
        if (hash == 120218)return 2125;
        if (hash == 97726)return 2126;
        if (hash == 110088)return 2127;
        if (hash == 119104)return 2128;
        if (hash == 94391)return 2129;
        if (hash == 5222)return 2130;
        if (hash == 130978)return 2131;
        if (hash == 53019)return 2132;
        if (hash == 176282)return 2133;
        if (hash == 181868)return 2134;
        if (hash == 69190)return 2135;
        if (hash == 165624)return 2136;
        if (hash == 30970)return 2137;
        if (hash == 68731)return 2138;
        if (hash == 34840)return 2139;
        if (hash == 124749)return 2140;
        if (hash == 187800)return 2141;
        if (hash == 108982)return 2142;
        if (hash == 83684)return 2143;
        if (hash == 108692)return 2144;
        if (hash == 71411)return 2145;
        if (hash == 93353)return 2146;
        if (hash == 115734)return 2147;
        if (hash == 182236)return 2148;
        if (hash == 202452)return 2149;
        if (hash == 33241)return 2150;
        if (hash == 18105)return 2151;
        if (hash == 37064)return 2152;
        if (hash == 5962)return 2153;
        if (hash == 19346)return 2154;
        if (hash == 52871)return 2155;
        if (hash == 32168)return 2156;
        if (hash == 176852)return 2157;
        if (hash == 171299)return 2158;
        if (hash == 169369)return 2159;
        if (hash == 8616)return 2160;
        if (hash == 81187)return 2161;
        if (hash == 163162)return 2162;
        if (hash == 3)return 2163;
        if (hash == 199106)return 2164;
        if (hash == 153806)return 2165;
        if (hash == 149302)return 2166;
        if (hash == 116542)return 2167;
        if (hash == 49030)return 2168;
        if (hash == 38964)return 2169;
        if (hash == 107341)return 2170;
        if (hash == 46790)return 2171;
        if (hash == 181996)return 2172;
        if (hash == 57291)return 2173;
        if (hash == 186284)return 2174;
        if (hash == 27594)return 2175;
        if (hash == 140675)return 2176;
        if (hash == 2132)return 2177;
        if (hash == 192018)return 2178;
        if (hash == 11169)return 2179;
        if (hash == 117259)return 2180;
        if (hash == 165683)return 2181;
        if (hash == 135506)return 2182;
        if (hash == 188584)return 2183;
        if (hash == 187661)return 2184;
        if (hash == 192689)return 2185;
        if (hash == 103524)return 2186;
        if (hash == 73609)return 2187;
        if (hash == 95163)return 2188;
        if (hash == 37300)return 2189;
        if (hash == 195616)return 2190;
        if (hash == 49323)return 2191;
        if (hash == 179761)return 2192;
        if (hash == 36535)return 2193;
        if (hash == 81826)return 2194;
        if (hash == 82050)return 2195;
        if (hash == 131213)return 2196;
        if (hash == 64461)return 2197;
        if (hash == 130565)return 2198;
        if (hash == 191638)return 2199;
        if (hash == 72528)return 2200;
        if (hash == 152805)return 2201;
        if (hash == 73598)return 2202;
        if (hash == 143052)return 2203;
        if (hash == 197020)return 2204;
        if (hash == 98041)return 2205;
        if (hash == 62762)return 2206;
        if (hash == 34705)return 2207;
        if (hash == 181265)return 2208;
        if (hash == 199048)return 2209;
        if (hash == 26305)return 2210;
        if (hash == 101022)return 2211;
        if (hash == 151535)return 2212;
        if (hash == 64733)return 2213;
        if (hash == 28452)return 2214;
        if (hash == 752)return 2215;
        if (hash == 80972)return 2216;
        if (hash == 189918)return 2217;
        if (hash == 134361)return 2218;
        if (hash == 116373)return 2219;
        if (hash == 162247)return 2220;
        if (hash == 147166)return 2221;
        if (hash == 117500)return 2222;
        if (hash == 139122)return 2223;
        if (hash == 105823)return 2224;
        if (hash == 163903)return 2225;
        if (hash == 163895)return 2226;
        if (hash == 135780)return 2227;
        if (hash == 120684)return 2228;
        if (hash == 57788)return 2229;
        if (hash == 24690)return 2230;
        if (hash == 143832)return 2231;
        if (hash == 145242)return 2232;
        if (hash == 166467)return 2233;
        if (hash == 142402)return 2234;
        if (hash == 141975)return 2235;
        if (hash == 51815)return 2236;
        if (hash == 36691)return 2237;
        if (hash == 22348)return 2238;
        if (hash == 7330)return 2239;
        if (hash == 75535)return 2240;
        if (hash == 92404)return 2241;
        if (hash == 155232)return 2242;
        if (hash == 188746)return 2243;
        if (hash == 152163)return 2244;
        if (hash == 34269)return 2245;
        if (hash == 92343)return 2246;
        if (hash == 2509)return 2247;
        if (hash == 156092)return 2248;
        if (hash == 59437)return 2249;
        if (hash == 113297)return 2250;
        if (hash == 36688)return 2251;
        if (hash == 131759)return 2252;
        if (hash == 125274)return 2253;
        if (hash == 128996)return 2254;
        if (hash == 55099)return 2255;
        if (hash == 54086)return 2256;
        if (hash == 126910)return 2257;
        if (hash == 59398)return 2258;
        if (hash == 92559)return 2259;
        if (hash == 179375)return 2260;
        if (hash == 157052)return 2261;
        if (hash == 105163)return 2262;
        if (hash == 172030)return 2263;
        if (hash == 141798)return 2264;
        if (hash == 44219)return 2265;
        if (hash == 14032)return 2266;
        if (hash == 79234)return 2267;
        if (hash == 12441)return 2268;
        if (hash == 118817)return 2269;
        if (hash == 98452)return 2270;
        if (hash == 3423)return 2271;
        if (hash == 12144)return 2272;
        if (hash == 155339)return 2273;
        if (hash == 103401)return 2274;
        if (hash == 180719)return 2275;
        if (hash == 43963)return 2276;
        if (hash == 108341)return 2277;
        if (hash == 184339)return 2278;
        if (hash == 138855)return 2279;
        if (hash == 139526)return 2280;
        if (hash == 129478)return 2281;
        if (hash == 119734)return 2282;
        if (hash == 46047)return 2283;
        if (hash == 143934)return 2284;
        if (hash == 171520)return 2285;
        if (hash == 64256)return 2286;
        if (hash == 81177)return 2287;
        if (hash == 63942)return 2288;
        if (hash == 182787)return 2289;
        if (hash == 46615)return 2290;
        if (hash == 170858)return 2291;
        if (hash == 91159)return 2292;
        if (hash == 97368)return 2293;
        if (hash == 20662)return 2294;
        if (hash == 35058)return 2295;
        if (hash == 54617)return 2296;
        if (hash == 184040)return 2297;
        if (hash == 70153)return 2298;
        if (hash == 139487)return 2299;
        if (hash == 31113)return 2300;
        if (hash == 884)return 2301;
        if (hash == 12994)return 2302;
        if (hash == 104725)return 2303;
        if (hash == 184362)return 2304;
        if (hash == 45287)return 2305;
        if (hash == 199554)return 2306;
        if (hash == 94578)return 2307;
        if (hash == 99704)return 2308;
        if (hash == 172710)return 2309;
        if (hash == 13614)return 2310;
        if (hash == 93516)return 2311;
        if (hash == 198941)return 2312;
        if (hash == 181153)return 2313;
        if (hash == 110521)return 2314;
        if (hash == 168332)return 2315;
        if (hash == 180739)return 2316;
        if (hash == 146519)return 2317;
        if (hash == 132928)return 2318;
        if (hash == 67602)return 2319;
        if (hash == 123980)return 2320;
        if (hash == 44599)return 2321;
        if (hash == 32142)return 2322;
        if (hash == 50780)return 2323;
        if (hash == 32141)return 2324;
        if (hash == 110598)return 2325;
        if (hash == 151056)return 2326;
        if (hash == 200010)return 2327;
        if (hash == 184038)return 2328;
        if (hash == 80826)return 2329;
        if (hash == 35548)return 2330;
        if (hash == 54756)return 2331;
        if (hash == 60678)return 2332;
        if (hash == 54262)return 2333;
        if (hash == 9299)return 2334;
        if (hash == 134941)return 2335;
        if (hash == 8648)return 2336;
        if (hash == 104210)return 2337;
        if (hash == 105948)return 2338;
        if (hash == 60641)return 2339;
        if (hash == 115190)return 2340;
        if (hash == 78908)return 2341;
        if (hash == 47472)return 2342;
        if (hash == 188126)return 2343;
        if (hash == 202331)return 2344;
        if (hash == 60208)return 2345;
        if (hash == 200170)return 2346;
        if (hash == 173774)return 2347;
        if (hash == 29159)return 2348;
        if (hash == 74082)return 2349;
        if (hash == 48023)return 2350;
        if (hash == 130573)return 2351;
        if (hash == 192819)return 2352;
        if (hash == 172671)return 2353;
        if (hash == 159705)return 2354;
        if (hash == 140255)return 2355;
        if (hash == 5275)return 2356;
        if (hash == 61947)return 2357;
        if (hash == 164130)return 2358;
        if (hash == 57766)return 2359;
        if (hash == 59700)return 2360;
        if (hash == 26499)return 2361;
        if (hash == 156894)return 2362;
        if (hash == 193421)return 2363;
        if (hash == 105083)return 2364;
        if (hash == 115931)return 2365;
        if (hash == 45552)return 2366;
        if (hash == 172564)return 2367;
        if (hash == 121654)return 2368;
        if (hash == 838)return 2369;
        if (hash == 50251)return 2370;
        if (hash == 139422)return 2371;
        if (hash == 160818)return 2372;
        if (hash == 118446)return 2373;
        if (hash == 158571)return 2374;
        if (hash == 1285)return 2375;
        if (hash == 115667)return 2376;
        if (hash == 134433)return 2377;
        if (hash == 144712)return 2378;
        if (hash == 772)return 2379;
        if (hash == 136857)return 2380;
        if (hash == 116041)return 2381;
        if (hash == 180641)return 2382;
        if (hash == 120927)return 2383;
        if (hash == 8339)return 2384;
        if (hash == 192980)return 2385;
        if (hash == 177884)return 2386;
        if (hash == 184491)return 2387;
        if (hash == 1192)return 2388;
        if (hash == 28461)return 2389;
        if (hash == 162768)return 2390;
        if (hash == 61560)return 2391;
        if (hash == 161086)return 2392;
        if (hash == 135114)return 2393;
        if (hash == 95180)return 2394;
        if (hash == 57980)return 2395;
        if (hash == 29370)return 2396;
        if (hash == 14254)return 2397;
        if (hash == 174718)return 2398;
        if (hash == 83547)return 2399;
        if (hash == 141473)return 2400;
        if (hash == 51614)return 2401;
        if (hash == 11396)return 2402;
        if (hash == 158744)return 2403;
        if (hash == 165278)return 2404;
        if (hash == 100795)return 2405;
        if (hash == 67581)return 2406;
        if (hash == 122686)return 2407;
        if (hash == 18972)return 2408;
        if (hash == 162016)return 2409;
        if (hash == 130106)return 2410;
        if (hash == 29119)return 2411;
        if (hash == 145910)return 2412;
        if (hash == 95141)return 2413;
        if (hash == 34782)return 2414;
        if (hash == 19653)return 2415;
        if (hash == 104036)return 2416;
        if (hash == 9810)return 2417;
        if (hash == 56464)return 2418;
        if (hash == 200062)return 2419;
        if (hash == 56376)return 2420;
        if (hash == 175362)return 2421;
        if (hash == 170770)return 2422;
        if (hash == 152832)return 2423;
        if (hash == 177133)return 2424;
        if (hash == 69469)return 2425;
        if (hash == 63973)return 2426;
        if (hash == 109947)return 2427;
        if (hash == 189602)return 2428;
        if (hash == 52224)return 2429;
        if (hash == 127783)return 2430;
        if (hash == 176608)return 2431;
        if (hash == 194314)return 2432;
        if (hash == 44246)return 2433;
        if (hash == 106098)return 2434;
        if (hash == 174605)return 2435;
        if (hash == 22815)return 2436;
        if (hash == 131773)return 2437;
        if (hash == 141363)return 2438;
        if (hash == 192221)return 2439;
        if (hash == 23781)return 2440;
        if (hash == 190801)return 2441;
        if (hash == 156613)return 2442;
        if (hash == 178377)return 2443;
        if (hash == 142587)return 2444;
        if (hash == 60882)return 2445;
        if (hash == 127515)return 2446;
        if (hash == 127493)return 2447;
        if (hash == 70735)return 2448;
        if (hash == 72709)return 2449;
        if (hash == 173706)return 2450;
        if (hash == 158631)return 2451;
        if (hash == 151536)return 2452;
        if (hash == 121297)return 2453;
        if (hash == 29263)return 2454;
        if (hash == 17597)return 2455;
        if (hash == 19909)return 2456;
        if (hash == 163439)return 2457;
        if (hash == 99170)return 2458;
        if (hash == 114929)return 2459;
        if (hash == 202130)return 2460;
        if (hash == 2163)return 2461;
        if (hash == 84014)return 2462;
        if (hash == 182862)return 2463;
        if (hash == 130947)return 2464;
        if (hash == 40330)return 2465;
        if (hash == 46937)return 2466;
        if (hash == 200004)return 2467;
        if (hash == 130913)return 2468;
        if (hash == 189568)return 2469;
        if (hash == 92591)return 2470;
        if (hash == 25943)return 2471;
        if (hash == 5362)return 2472;
        if (hash == 55326)return 2473;
        if (hash == 104696)return 2474;
        if (hash == 54460)return 2475;
        if (hash == 11254)return 2476;
        if (hash == 42123)return 2477;
        if (hash == 78354)return 2478;
        if (hash == 83578)return 2479;
        if (hash == 167805)return 2480;
        if (hash == 47149)return 2481;
        if (hash == 39990)return 2482;
        if (hash == 183914)return 2483;
        if (hash == 183150)return 2484;
        if (hash == 156588)return 2485;
        if (hash == 131553)return 2486;
        if (hash == 178463)return 2487;
        if (hash == 79109)return 2488;
        if (hash == 43270)return 2489;
        if (hash == 127312)return 2490;
        if (hash == 13089)return 2491;
        if (hash == 172039)return 2492;
        if (hash == 156973)return 2493;
        if (hash == 14027)return 2494;
        if (hash == 39201)return 2495;
        if (hash == 71885)return 2496;
        if (hash == 136394)return 2497;
        if (hash == 169069)return 2498;
        if (hash == 101419)return 2499;
        if (hash == 95229)return 2500;
        if (hash == 90394)return 2501;
        if (hash == 150667)return 2502;
        if (hash == 198435)return 2503;
        if (hash == 16432)return 2504;
        if (hash == 107630)return 2505;
        if (hash == 49331)return 2506;
        if (hash == 116150)return 2507;
        if (hash == 78839)return 2508;
        if (hash == 56395)return 2509;
        if (hash == 91968)return 2510;
        if (hash == 115545)return 2511;
        if (hash == 31060)return 2512;
        if (hash == 61008)return 2513;
        if (hash == 199645)return 2514;
        if (hash == 124531)return 2515;
        if (hash == 165814)return 2516;
        if (hash == 85298)return 2517;
        if (hash == 75315)return 2518;
        if (hash == 85558)return 2519;
        if (hash == 155573)return 2520;
        if (hash == 197667)return 2521;
        if (hash == 96700)return 2522;
        if (hash == 81564)return 2523;
        if (hash == 103307)return 2524;
        if (hash == 6189)return 2525;
        if (hash == 147709)return 2526;
        if (hash == 18482)return 2527;
        if (hash == 20963)return 2528;
        if (hash == 38805)return 2529;
        if (hash == 187878)return 2530;
        if (hash == 64407)return 2531;
        if (hash == 109711)return 2532;
        if (hash == 25613)return 2533;
        if (hash == 187720)return 2534;
        if (hash == 153280)return 2535;
        if (hash == 168910)return 2536;
        if (hash == 194389)return 2537;
        if (hash == 201601)return 2538;
        if (hash == 36128)return 2539;
        if (hash == 126969)return 2540;
        if (hash == 118802)return 2541;
        if (hash == 118556)return 2542;
        if (hash == 88684)return 2543;
        if (hash == 164738)return 2544;
        if (hash == 199768)return 2545;
        if (hash == 189751)return 2546;
        if (hash == 163152)return 2547;
        if (hash == 112642)return 2548;
        if (hash == 149536)return 2549;
        if (hash == 190211)return 2550;
        if (hash == 60891)return 2551;
        if (hash == 96356)return 2552;
        if (hash == 150130)return 2553;
        if (hash == 28936)return 2554;
        if (hash == 180763)return 2555;
        if (hash == 165689)return 2556;
        if (hash == 146528)return 2557;
        if (hash == 90207)return 2558;
        if (hash == 56137)return 2559;
        if (hash == 81654)return 2560;
        if (hash == 26893)return 2561;
        if (hash == 115595)return 2562;
        if (hash == 21454)return 2563;
        if (hash == 63232)return 2564;
        if (hash == 56818)return 2565;
        if (hash == 126039)return 2566;
        if (hash == 204139)return 2567;
        if (hash == 178076)return 2568;
        if (hash == 1718)return 2569;
        if (hash == 32826)return 2570;
        if (hash == 17759)return 2571;
        if (hash == 156904)return 2572;
        if (hash == 22669)return 2573;
        if (hash == 175432)return 2574;
        if (hash == 90807)return 2575;
        if (hash == 70820)return 2576;
        if (hash == 115555)return 2577;
        if (hash == 78412)return 2578;
        if (hash == 115524)return 2579;
        if (hash == 134764)return 2580;
        if (hash == 41570)return 2581;
        if (hash == 179811)return 2582;
        if (hash == 80687)return 2583;
        if (hash == 61153)return 2584;
        if (hash == 146357)return 2585;
        if (hash == 125731)return 2586;
        if (hash == 63301)return 2587;
        if (hash == 9800)return 2588;
        if (hash == 150165)return 2589;
        if (hash == 190848)return 2590;
        if (hash == 128429)return 2591;
        if (hash == 71783)return 2592;
        if (hash == 192871)return 2593;
        if (hash == 93635)return 2594;
        if (hash == 156439)return 2595;
        if (hash == 202675)return 2596;
        if (hash == 40516)return 2597;
        if (hash == 191242)return 2598;
        if (hash == 20713)return 2599;
        if (hash == 106740)return 2600;
        if (hash == 37785)return 2601;
        if (hash == 86398)return 2602;
        if (hash == 23345)return 2603;
        if (hash == 196868)return 2604;
        if (hash == 39338)return 2605;
        if (hash == 74414)return 2606;
        if (hash == 82919)return 2607;
        if (hash == 139005)return 2608;
        if (hash == 44898)return 2609;
        if (hash == 174401)return 2610;
        if (hash == 23484)return 2611;
        if (hash == 189879)return 2612;
        if (hash == 8391)return 2613;
        if (hash == 47502)return 2614;
        if (hash == 91850)return 2615;
        if (hash == 61637)return 2616;
        if (hash == 130757)return 2617;
        if (hash == 134106)return 2618;
        if (hash == 86355)return 2619;
        if (hash == 146255)return 2620;
        if (hash == 71957)return 2621;
        if (hash == 157946)return 2622;
        if (hash == 90296)return 2623;
        if (hash == 164533)return 2624;
        if (hash == 45288)return 2625;
        if (hash == 96019)return 2626;
        if (hash == 20576)return 2627;
        if (hash == 144569)return 2628;
        if (hash == 200214)return 2629;
        if (hash == 14553)return 2630;
        if (hash == 132767)return 2631;
        if (hash == 69521)return 2632;
        if (hash == 167408)return 2633;
        if (hash == 8794)return 2634;
        if (hash == 168395)return 2635;
        if (hash == 154335)return 2636;
        if (hash == 57430)return 2637;
        if (hash == 118746)return 2638;
        if (hash == 99331)return 2639;
        if (hash == 111605)return 2640;
        if (hash == 96535)return 2641;
        if (hash == 180035)return 2642;
        if (hash == 107768)return 2643;
        if (hash == 107809)return 2644;
        if (hash == 44716)return 2645;
        if (hash == 9019)return 2646;
        if (hash == 20050)return 2647;
        if (hash == 185722)return 2648;
        if (hash == 117083)return 2649;
        if (hash == 142080)return 2650;
        if (hash == 91498)return 2651;
        if (hash == 116466)return 2652;
        if (hash == 23986)return 2653;
        if (hash == 146361)return 2654;
        if (hash == 8231)return 2655;
        if (hash == 97577)return 2656;
        if (hash == 151937)return 2657;
        if (hash == 45573)return 2658;
        if (hash == 200166)return 2659;
        if (hash == 144156)return 2660;
        if (hash == 61161)return 2661;
        if (hash == 175626)return 2662;
        if (hash == 174855)return 2663;
        if (hash == 9511)return 2664;
        if (hash == 36852)return 2665;
        if (hash == 183572)return 2666;
        if (hash == 138294)return 2667;
        if (hash == 92137)return 2668;
        if (hash == 131554)return 2669;
        if (hash == 132161)return 2670;
        if (hash == 55725)return 2671;
        if (hash == 187592)return 2672;
        if (hash == 34504)return 2673;
        if (hash == 146959)return 2674;
        if (hash == 116788)return 2675;
        if (hash == 38166)return 2676;
        if (hash == 190229)return 2677;
        if (hash == 30308)return 2678;
        if (hash == 116864)return 2679;
        if (hash == 137891)return 2680;
        if (hash == 144097)return 2681;
        if (hash == 113895)return 2682;
        if (hash == 53877)return 2683;
        if (hash == 8236)return 2684;
        if (hash == 145125)return 2685;
        if (hash == 79247)return 2686;
        if (hash == 110355)return 2687;
        if (hash == 80164)return 2688;
        if (hash == 59057)return 2689;
        if (hash == 148625)return 2690;
        if (hash == 104925)return 2691;
        if (hash == 151288)return 2692;
        if (hash == 189742)return 2693;
        if (hash == 42366)return 2694;
        if (hash == 13050)return 2695;
        if (hash == 104359)return 2696;
        if (hash == 104350)return 2697;
        if (hash == 112710)return 2698;
        if (hash == 142559)return 2699;
        if (hash == 125872)return 2700;
        if (hash == 5922)return 2701;
        if (hash == 158533)return 2702;
        if (hash == 83065)return 2703;
        if (hash == 24288)return 2704;
        if (hash == 24287)return 2705;
        if (hash == 9192)return 2706;
        if (hash == 71000)return 2707;
        if (hash == 165911)return 2708;
        if (hash == 122842)return 2709;
        if (hash == 37067)return 2710;
        if (hash == 151852)return 2711;
        if (hash == 203198)return 2712;
        if (hash == 124162)return 2713;
        if (hash == 2186)return 2714;
        return -1;
    }

    inline short trainStation2Short(const myAlgorithm::String &station) {
        //TODO : Hash
        return 1;
    }

    inline myAlgorithm::String short2trainStation(const short &idx) {
//        return InternalData::InternalStation[idx];
    }

    inline short trainTicketKind2Short(const myAlgorithm::String &tkd) {

        return 1;
    }

    inline myAlgorithm::String short2trainTicketKind(const short &idx) {

        return "";
    }

    void _init() {
        if (access("id.dat", 0) == -1) {
            FILE *tmpfp = fopen("id.dat", "wb+");
            fclose(tmpfp);
        }
        FILE *fp;
        fp = fopen("id.dat", "rw+");
        fscanf(fp, "%d%d", &nowId, &ticketId);
        fclose(fp);
    }

    void _exit() {
        FILE *fp = fopen("id.dat", "w+");
        fprintf(fp, "%d\n%d\n", nowId, ticketId);
        fclose(fp);
#ifdef _NO_DEBUG
        userIdTree.closeFile();
        ticketTree.closeFile();
        ticketIdTree.closeFile();
        userTicketTree.closeFile();
        trainTree.closeFile();
#endif
    }

    class Interface {
    public:
        ~Interface() {}
    };

    class Insert : public Interface {
    public:
        Insert() {}

        Status
        I_addUser(const String &p_name, const String &p_word, const String &p_email, const String &p_phone, int &p_id) {
            /*auto nameHasExisted = userNameTree.search(p_name);
            if (nameHasExisted.second) {
                p_id = 0;
                return NameHasExisted;
            }*/
            user newUser(nowId, p_name, p_word, p_email, p_phone);
            p_id = nowId++;
            userIdTree.insert(p_id, newUser);
            //userNameTree.insert(p_name, p_id);
            return Success;
        }

        Status I_addUserBookedTicket(int p_id, int tk_num, String tk_id, Pair<short, short> tk_position, Date tk_date,
                                     int tk_kind) {
            auto userSel = userIdTree.search(p_id);
            if (!userSel.second)
                return NoThisUser;
            ticketKey newTk(tk_position, tk_id, tk_date);
            auto tkSel = ticketTree.search(newTk);
            if (!tkSel.second)
                return NoThisTrain;
            auto trSel = trainTree.search(tk_id);
            if (!trSel.second)
                return NoThisTrain;
            train upTrain(trSel.first);
            short i, j;
            for (i = 0; i < upTrain.t_stationNum; ++i)
                if (i == tk_position.first())
                    break;
            for (j = 0; j < upTrain.t_stationNum; ++j)
                if (j == tk_position.second())
                    break;
            if (i >= j || i == upTrain.t_stationNum || j == upTrain.t_stationNum)
                return NoThisTrain;
            Vector<ticketKey> vtk;
            for (short k = i; k < j; ++k) {
                ticketKey tik(Pair<short, short>(upTrain.t_station[k], upTrain.t_station[k + 1]),
                              tk_id, tk_date);
                auto tikSel = ticketTree.search(tik);
                if (!tikSel.second || tikSel.first.tk_remain[tk_kind] < tk_num)
                    return NoRemainTicket;
                else
                    vtk.push_back(tik);
            }
            for (int i = 0; i < vtk.size(); ++i) {
                auto tikSel = ticketTree.search(vtk[i]);
                tikSel.first.tk_remain[tk_kind] -= tk_num;
                if (tikSel.first.tk_remain[tk_kind] == 0)
                    ticketTree.erase(vtk[i]);
                else
                    ticketTree.update(vtk[i], tikSel.first);
            }
            int ticketID = tkSel.first.tk_ticketID;
            userTicketTree.insert(Pair<int, int>(p_id, ticketID), Pair<int, int>(ticketID, tk_num));
            return Success;
        }

        Status I_addTrain(const String &t_id, const String &t_name, int t_catalog, short t_sNum, short t_tKind,
                          short *t_tname) {
            train newTrain;
            newTrain.t_id = t_id;
            newTrain.t_name = t_name;
            newTrain.t_catalog = t_catalog;
            newTrain.t_ticketKind = t_tKind;
            newTrain.t_onSale = false;
            for (short i = 0; i < t_tKind; ++i)
                newTrain.t_ticketName[i] = t_tname[i];
            trainTree.insert(t_id, newTrain);
            return Success;
        }

        Status I_addTrainTicket(const String &tk_id, int t_stationNum, float *t_priceNum) {
            auto trSel = trainTree.search(tk_id);
            if (!trSel.second)
                return NoThisTrain;
            train upTrain = trSel.first;
            upTrain.t_station[upTrain.t_stationNum] = t_stationNum;
            if (upTrain.t_stationNum != 0) {
                for (short i = 0; i < upTrain.t_ticketKind; ++i)
                    upTrain.t_price[upTrain.t_stationNum][i] =
                            upTrain.t_price[upTrain.t_stationNum - 1][i] + t_priceNum[i];
            }
            ++upTrain.t_stationNum;
            return Success;
        }

        ~Insert() {}
    };

    class Select : public Interface {
    public:
        Select() {}

        Status I_selectUser(int p_id, String p_word) {
            auto userSel = userIdTree.search(p_id);
            if (!userSel.second) {
                return NoThisUser;
            }
            if (userSel.first.M_password() != p_word)
                return NoThisUser;
            return Success;
        }

        /*Status I_selectUser(String p_name, String p_word) {
            auto userNameSel = userNameTree.search(p_name);
            if (!userNameSel.second)
                return NoThisUser;
            auto userSel = userIdTree.search(userNameSel.first);
            if (!userSel.second)
                return NoThisUser;
            if (userSel.first.M_password() != p_word)
                return NoThisUser;
            return Success;
        }*/

        Status I_selectUser(int p_id, String &p_name, String &p_email, String &p_phone, UserPrivilege &up) {
            auto userSel = userIdTree.search(p_id);
            if (!userSel.second)
                return NoThisUser;
            p_name = userSel.first.M_username();
            p_email = userSel.first.M_email();
            p_phone = userSel.first.M_phone();
            up = userSel.first.M_privilege();
            return Success;
        }

        Status I_selectTicket(Pair<short, short> tk_position, Date tk_date, short tk_catalog, Vector<ticket> &ret) {
            ret.clear();
            ticketKey tkKey(tk_position, tk_date);
            Vector<ticket> vt = ticketTree.searchFirstAndSecond(tkKey);
            for (int i = 0; i < vt.size(); ++i) {

                auto trSel = trainTree.search(vt[i].tk_trainID);
                if (trSel.first.t_catalog & tk_catalog)
                    ret.push_back(vt[i]);
            }
            if (ret.empty())
                return NoThisTrain;
            else
                return Success;
        }

        Status I_selectTicketTransfer(Pair<short, short> tk_position, Date tk_date, short tk_catalog,
                                      short totStation, Vector<ticket> &ret) {
            ret.clear();
            Vector<ticket> vt1, vt2;
            ticket ans1, ans2;
            int minTime;
            for (short i = 0; i < totStation; ++i) {
                if (i != tk_position.first() && i != tk_position.second())
                    I_selectTicket(Pair<short, short>(tk_position.first(), i), tk_date, tk_catalog, vt1);
                I_selectTicket(Pair<short, short>(i, tk_position.second()), tk_date, tk_catalog, vt2);
                for (int j = 0; j < vt1.size(); ++j) {
                    for (int k = 0; k < vt2.size(); ++k) {
                        if (minTime < vt2[k].tk_time.second() - vt1[j].tk_time.first()) {
                            minTime = vt2[k].tk_time.second() - vt1[j].tk_time.first();
                            ans1 = vt1[j];
                            ans2 = vt2[k];
                        }
                    }
                }
            }
            if (ans1.tk_ticketID == 0 || ans2.tk_ticketID == 0)
                return NoThisTrain;
            ret.push_back(ans1);
            ret.push_back(ans2);
            return Success;
        }

        Status I_selectUserBookedTicket(int p_id, Date p_date, int tk_catalog, Vector<ticket> &ret, Vector<int> &num) {
            ret.clear();
            auto userSel = userIdTree.search(p_id);
            if (!userSel.second)
                return NoThisUser;
            auto vb = userTicketTree.searchFirst(Pair<int, int>(p_id, 0));
            for (int i = 0; i < vb.size(); ++i) {
                auto tikSel = ticketIdTree.search(vb[i].first());
                if (tikSel.second && tikSel.first.tk_date == p_date && tikSel.first.tk_catalog & tk_catalog) {
                    ret.push_back(tikSel.first);
                    num.push_back(vb[i].second());
                }
            }
            if (ret.empty())
                return NoTicketBooked;
            return Success;
        }

        Status I_selectTrain(const String &p_id, train &ret) {
            auto trainSel = trainTree.search(p_id);
            if (!trainSel.second)
                return NoThisTrain;
            ret = trainSel.first;
            return Success;
        }

        ~Select() {}
    };

    class Update : public Interface {
    public:
        Update() {}

        Status I_updateUser(int p_id, const String &p_name, const String &p_pwd, const String &p_email,
                            const String &p_phone) {
            auto userSel = userIdTree.search(p_id);
            if (!userSel.second)
                return NoThisUser;
            user newUser = userSel.first;
            newUser.p_username = p_name;
            newUser.p_password = p_pwd;
            newUser.p_email = p_email;
            newUser.p_phone = p_phone;
            userIdTree.update(p_id, newUser);
            return Success;
        }

        Status I_updateUserPrivilege(int p_id, int p_id2, int p_privilege) {
            auto user1Sel = userIdTree.search(p_id);
            auto user2Sel = userIdTree.search(p_id2);
            if (!user1Sel.second || !user2Sel.second)
                return NoThisUser;
            if (user1Sel.first.p_userPrivilege != Admin)
                return NoPrivilege;
            if (user2Sel.first.p_userPrivilege == Admin && p_privilege == 1)
                return NoPrivilege;
            user2Sel.first.p_userPrivilege = (p_privilege == 1 ? User : Admin);
            userIdTree.update(p_id2, user2Sel.first);
            return Success;
        }

        Status I_updateTrainSellingStatus(const String &t_id) {
            auto trSel = trainTree.search(t_id);
            if (!trSel.second)
                return NoThisTrain;
            if (trSel.first.t_onSale)
                return TrainHasBeenOnSale;
            train tr = trSel.first;
            for (short i = 0; i < tr.t_stationNum; ++i) {
                for (short j = i + 1; j < tr.t_stationNum; ++j) {
                    for (Date d = startDate; d != endDate; d = d.nextDate()) {
                        ticket newTik;
                        newTik.tk_position = Pair<short, short>(tr.t_station[i], tr.t_station[j]);
                        newTik.tk_time = Pair<Time, Time>(tr.t_time[i], tr.t_time[j]);
                        newTik.tk_date = d;
                        newTik.tk_catalog = tr.t_catalog;
                        newTik.tk_ticketID = ticketId++;
                        newTik.tk_trainID = tr.t_id;
                        for (short p = 0; p != 5; ++p) {
                            newTik.tk_remain[p] = 2000;
                            newTik.tk_price[p] = tr.t_price[j][p] - tr.t_price[i][p];
                        }
                        ticketTree.insert(ticketKey(newTik), newTik);
                        ticketIdTree.insert(newTik.tk_ticketID, newTik);
                    }
                }
            }
            return Success;
        }

        Status I_updateTrain(const String &t_id, const train &data) {
            auto trainSel = trainTree.search(t_id);
            if (!trainSel.second)
                return NoThisTrain;
            if (trainSel.first.t_onSale)
                return TrainHasBeenOnSale;
            trainTree.update(t_id, data);
            return Success;
        }

        ~Update() {}
    };

    class Delete : public Interface {
    public:
        Delete() {}

        Status I_deleteUserBookedTicket(int p_id, Date p_date, const String &tk_id, Pair<short, short> tk_location,
                                        int tk_kind, int tk_num) {
            auto userSel = userIdTree.search(p_id);
            if (!userSel.second)
                return NoThisUser;
            auto tik = userTicketTree.searchFirst(Pair<int, int>(p_id, 0));
            if (tik.empty())
                return NoRemainTicket;
            for (int i = 0; i < tik.size(); ++i) {
                auto tikIdSel = ticketIdTree.search(tik[i].first());
                if (!tikIdSel.second)
                    continue;
                if (tikIdSel.first.tk_date != p_date
                    || tikIdSel.first.tk_position != tk_location
                    || tikIdSel.first.tk_trainID != tk_id)
                    continue;
                if (tik[i].second() < tk_num)
                    return NoRemainTicket;
                if (tik[i].second() == tk_num)
                    userTicketTree.erase(Pair<int, int>(p_id, tik[i].first()));
                else
                    userTicketTree.update(Pair<int, int>(p_id, tik[i].first()),
                                          Pair<int, int>(tik[i].first(), tik[i].second() - tk_num));
                auto tikSel = ticketTree.search(ticketKey(tikIdSel.first));
                if (tikSel.second) {
                    tikIdSel.first.tk_remain[tk_kind] += tk_num;
                    ticketTree.update(ticketKey(tikIdSel.first), tikIdSel.first);
                } else {
                    ticket newTik = tikSel.first;
                    newTik.tk_remain[tk_kind] = tk_num;
                    ticketTree.insert(ticketKey(newTik), newTik);
                }
                return Success;
            }
            return NoRemainTicket;
        }

        Status I_deleteTrain(const String &p_id) {
            auto trainSel = trainTree.search(p_id);
            if (!trainSel.second)
                return NoThisTrain;
            if (trainSel.first.t_onSale)
                return TrainHasBeenOnSale;
            trainTree.erase(p_id);
            return Success;
        }

        Status I_deleteAll() {
            userIdTree.clear();
            ticketTree.clear();
            ticketIdTree.clear();
            userTicketTree.clear();
            trainTree.clear();
            FILE *fp = fopen("id.dat", "w+");
            fprintf(fp, "2018\n1\n");
            fclose(fp);
            nowId = 2018;
            ticketId = 1;
            return Success;
        }

        ~Delete() {}
    };

}


#endif //INC_2018DATASTRUCTUREBIGWORK_KERNEL_HPP
