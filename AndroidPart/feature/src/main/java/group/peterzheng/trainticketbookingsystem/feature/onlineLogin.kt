package group.peterzheng.trainticketbookingsystem.feature

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import kotlinx.android.synthetic.main.online_login_layout.*
import kotlin.math.log

class onlineLogin : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.online_login_layout)

        initView()
    }

    fun initView() {
        loginResult.visibility = TextView.INVISIBLE

        clearButton.setOnClickListener {
            passName.setText("")
            passWord.setText("")
        }

        loginButton.setOnClickListener {
            var result: Boolean
            result = DataCenter.Companion.Query.Companion.QueryUser(passName.text.toString(), passWord.text.toString());
            loginResult.visibility = TextView.INVISIBLE
            if (result) {
                loginResult.setText("登录成功！")
                println("用户名 " + passName.text.toString() + " 密码 " + passWord.text.toString() + " 登录成功！")
            } else{
                loginResult.setText("登录失败！密码错误！")
                println("用户名 " + passName.text.toString() + " 密码 " + passWord.text.toString() + " 登录失败！")
            }
        }
    }
}
