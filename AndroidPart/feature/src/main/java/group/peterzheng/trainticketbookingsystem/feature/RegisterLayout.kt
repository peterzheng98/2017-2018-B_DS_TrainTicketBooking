package group.peterzheng.trainticketbookingsystem.feature

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import group.peterzheng.trainticketbookingsystem.feature.R.id.register
import group.peterzheng.trainticketbookingsystem.feature.R.id.registerButton
import kotlinx.android.synthetic.main.activity_register_layout.*
import kotlinx.android.synthetic.main.online_login_layout.*

class RegisterLayout : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_register_layout)

        initView()
    }

    fun initView() {
        registerResult.visibility = TextView.INVISIBLE

        var flagName : Boolean = false
        var flagWord : Boolean = false

        var stringName : String = ""
        var stringWord : String = ""

        registerCheckUser.setOnClickListener {
            registerResult.visibility = TextView.VISIBLE
            var l : Int = registerName.text.length
            flagName = false
            when {
                registerName.text.toString() == "hzfengsy" -> registerResult.setText("该用户已被ban！")
                l == 0 -> registerResult.setText("用户名不能为空！")
                l < 6 || l > 32 -> registerResult.setText("用户名长度应在6到32之间！")
                else -> {
                    flagName = true
                    var a : String = registerName.text.toString()
                    for(i in 0..l - 1)
                        if(!((a[i] >= 'a' && a[i] <= 'z') || (a[i] >= 'A' && a[i] <= 'Z') || (a[i] >= '0' && a[i] <= '9') || a[i] == '_')) {
                            registerResult.setText("用户名只能包含大小写字母或数字或'_'！")
                            flagName = false
                            break
                        }
                    if(flagName == true){
                        //TODO
                        stringName = a
                        registerResult.setText("用户名正确！")
                    }
                }
            }
        }

        registerCheckWord.setOnClickListener {
            registerResult.visibility = TextView.VISIBLE
            var l : Int = registerWord.text.length
            flagWord = false
            when {
                l == 0 -> registerResult.setText("密码不能为空！")
                l < 6 || l > 32 -> registerResult.setText("密码长度应在6到32之间！")
                else -> {
                    flagWord = true
                    var a : String = registerWord.text.toString()
                    for(i in 0..l - 1)
                        if(!((a[i] >= 'a' && a[i] <= 'z') || (a[i] >= 'A' && a[i] <= 'Z') || (a[i] >= '0' && a[i] <= '9') || a[i] == '_' || a[i] == '!' || a[i] == '?')) {
                            registerResult.setText("密码只能包含大小写字母或数字或'_,!,?'！")
                            flagWord = false
                            break
                        }
                    if(flagWord == true) {
                        stringWord  = a
                        registerResult.setText("密码正确！")
                    }
                }
            }
        }

        register.setOnClickListener{
            registerResult.visibility = TextView.VISIBLE
            when {
                stringName != registerName.text.toString() -> registerResult.setText("请重新验证用户名！")
                stringWord != registerWord.text.toString() -> registerResult.setText("请重新验证密码！")
                flagName == false -> registerResult.setText("请先验证用户名！")
                flagWord == false -> registerResult.setText("请先验证密码！")
                registerPhone.text.isEmpty() -> registerResult.setText("手机号不能为空！")
                registerPhone.text.length != 11 -> registerResult.setText("请输入正确的手机号！")
                registerMail.text.isEmpty() -> registerResult.setText("邮箱地址不能为空！")
                else -> {
                    var a : String = registerMail.text.toString()
                    var l : Int = a.length
                    var cnt : Int = 0
                    for(i in 0..l - 1)
                        if(a[i] == '@')cnt++
                    if(cnt != 1)registerResult.setText("请输入正确的邮箱地址！")
                    else
                    {
                        DataCenter.Companion.UserState.UserName = stringName
                        DataCenter.Companion.UserState.UserLevel = 0
                        registerResult.setText("注册成功")
                        var intent = Intent()
                        intent.setClass(this, ControlPanel::class.java)
                        startActivity(intent)
                        //TODO
                    }
                }
            }
        }
    }
}
