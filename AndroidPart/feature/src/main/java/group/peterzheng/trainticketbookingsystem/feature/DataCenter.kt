package group.peterzheng.trainticketbookingsystem.feature

class DataCenter {
    companion object {
        class LoginScreen {
            companion object {
                public var lockLoginOffline: Boolean = false
                public var lockTestConnection: Boolean = false
                public var lockLoginOnline: Boolean = false
                public var connectTestResult : Boolean = false
            }

        }

        class UserState{
            companion object {
                public var UserName : String = ""
                public var UserWord : String = ""
                public var UserLevel : Int = 0
                public var UserLoginResult : Int = -1
            }
        }

        class NetworkInfo{
            companion object {
                public var ipAddressURL : String = ""
                public var ipPort : Int = 0
            }
        }

        class Query{
            companion object {
                fun QueryUser(userName : String, userWord : String) : Boolean {
                    //For Debug ONLY
                    return userWord == "Test" && userName != "Hzfengsy"
                }
            }
        }
    }
}