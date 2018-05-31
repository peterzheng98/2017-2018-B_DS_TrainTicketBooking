package group.peterzheng.trainticketbookingsystem.feature

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import kotlinx.android.synthetic.main.online_login_layout.*
import kotlin.math.log
import android.content.Intent
class onlineLogin : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.online_login_layout)

        initView()

        if (DataCenter.Companion.UserState.Companion.UserLoginResult != -1) {
            passName.setText(DataCenter.Companion.UserState.UserName);
            passWord.setText(DataCenter.Companion.UserState.UserWord);
            loginResult.setText("您已登录，请直接单击登录按钮")
        }
    }

    fun initView() {
        loginResult.visibility = TextView.INVISIBLE

        clearButton.setOnClickListener {
            passName.setText("")
            passWord.setText("")
        }

        loginButton.setOnClickListener {
            if (DataCenter.Companion.UserState.Companion.UserLoginResult != -1) {
                // Intent to next page
            } else {
                var result: Boolean
                result = DataCenter.Companion.Query.Companion.QueryUser(passName.text.toString(), passWord.text.toString());
                loginResult.visibility = TextView.VISIBLE
                if (result) {
                    loginResult.setText("登录成功！")
                    println("用户名 " + passName.text.toString() + " 密码 " + passWord.text.toString() + " 登录成功！")
                } else {
                    loginResult.setText("登录失败！密码错误！")
                    println("用户名 " + passName.text.toString() + " 密码 " + passWord.text.toString() + " 登录失败！")
                }
            }
        }

        registerButton.setOnClickListener{
            var intent = Intent()
            intent.setClass(this, RegisterLayout::class.java)
            startActivity(intent)
        }
    }
}
