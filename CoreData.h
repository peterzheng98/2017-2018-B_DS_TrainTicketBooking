//
// Created by Peter Zheng on 2018/04/10.
//

#ifndef INC_2018DATASTRUCTUREBIGWORK_COREDATA_H
#define INC_2018DATASTRUCTUREBIGWORK_COREDATA_H

enum Status{
    Success,
    NoThisUser,
    NoRemainTicket,
    NoThisTrain,
};

enum UserPrivilege{
    Admin,
    User,
    NotRegister,
};

enum TicketOnSale{
    Available,
    Unavailable
};

namespace myAlgorithm{
    template <class T, class U>
    class Pair{

    };

    class Date{

    };

    template <class T>
    class Vector{

    };

    template <class T>
    class Set{

    };
    template <class T>
    class BigNum{

    };
}


#endif //INC_2018DATASTRUCTUREBIGWORK_COREDATA_H
