package group.peterzheng.trainticketbookingsystem.feature

import android.content.Context
import android.content.Intent
import android.net.ConnectivityManager
import android.os.Bundle
import android.os.Message
import android.os.WorkSource
import android.support.design.widget.Snackbar
import android.support.v7.app.AppCompatActivity
import android.util.Log
import android.view.Menu
import android.view.MenuItem
import android.widget.Button
import android.widget.ProgressBar
import android.widget.TextView
import android.widget.Toast
import com.fasterxml.jackson.annotation.ObjectIdGenerators
import com.github.kittinunf.fuel.core.response
import com.github.kittinunf.fuel.httpGet
import com.github.kittinunf.result.Result
import group.peterzheng.trainticketbookingsystem.feature.DataCenter.*

import kotlinx.android.synthetic.main.activity_main.*
import kotlinx.android.synthetic.main.content_main.*
import java.util.logging.Handler

class MainActivity : AppCompatActivity() {
    var ipAddressT: TextView? = null
    var ipPortT: TextView? = null
    var testConnB: Button? = null
    var loginOfflineB: Button? = null
    var loginOnlineB: Button? = null
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        setSupportActionBar(toolbar)

        fab.setOnClickListener { view ->
            Snackbar.make(view, "正在测试中", Snackbar.LENGTH_LONG)
                    .setAction("Action", null).show()
        }

        // Example of a call to a native method
//        sample_text.text = stringFromJNI()
        // 隐藏不需要的模块
        textStatus.visibility = TextView.INVISIBLE
        testProgress.visibility = ProgressBar.INVISIBLE

        initView()

    }

    // 绑定各个控件
    fun initView() {
        ipAddressT = findViewById<TextView>(R.id.ipAddr)
        ipPortT = findViewById<TextView>(R.id.ipPort)
        testConnB = findViewById<Button>(R.id.testConn)
        loginOnlineB = findViewById<Button>(R.id.loginOnline)
        loginOfflineB = findViewById<Button>(R.id.loginOffline)

        //关闭端口连接体
        ipPort.visibility = TextView.INVISIBLE
        textView3.visibility = TextView.INVISIBLE

        loginOnline.visibility = Button.INVISIBLE
        //绑定按钮监听
        loginOfflineB!!.setOnClickListener {
            if (!DataCenter.Companion.LoginScreen.lockLoginOffline) {
                textStatus.visibility = TextView.VISIBLE
                textStatus!!.setText("正在加载数据登录系统")
                testProgress.visibility = ProgressBar.VISIBLE
                DataCenter.Companion.LoginScreen.lockLoginOffline = true
            } else {
                Toast.makeText(baseContext, "正在加载请勿重复单击按钮！", Toast.LENGTH_SHORT).show()
            }

        }
        testConnB!!.setOnClickListener {
            if (!DataCenter.Companion.LoginScreen.lockTestConnection) {
                textStatus.visibility = TextView.VISIBLE
                textStatus!!.setText("正在测试连接")
                testProgress.visibility = ProgressBar.VISIBLE;
                DataCenter.Companion.LoginScreen.lockTestConnection = true
                try {
                    val TestURL: String = "http://" + ipAddr.text + "/test.lglo"
                    TestURL.httpGet().responseString { request, response, result ->
                        when (result) {
                            is Result.Success -> {
                                println("Result: ${result.get()}")
                                Toast.makeText(baseContext, "连接成功！", Toast.LENGTH_SHORT).show()
                                textStatus!!.setText("连接成功！")
                                testProgress.visibility = ProgressBar.INVISIBLE
                                loginOnline.visibility = Button.VISIBLE
                                testConn.visibility = Button.INVISIBLE
                                DataCenter.Companion.LoginScreen.connectTestResult = true
                            }
                            is Result.Failure -> {
                                println("Result: ${result.get()}  Request: ${request.headers}  Response: ${response.responseMessage}")
                                Toast.makeText(baseContext, "连接失败！", Toast.LENGTH_SHORT).show()
                                DataCenter.Companion.LoginScreen.lockTestConnection = false
                            }
                        }
                    }
                } catch (e: Exception) {
                    Log.e("MainActivity", "Runtime Error in testConnB(setOnClickedListener) , Message: " + e.toString());
                    Toast.makeText(baseContext, "发生运行时错误！", Toast.LENGTH_SHORT).show()
                }

            } else {
                if (DataCenter.Companion.LoginScreen.connectTestResult)
                    Toast.makeText(baseContext, "已经测试成功，请登录", Toast.LENGTH_SHORT).show()
                else
                    Toast.makeText(baseContext, "正在测试连接，请勿重复单击", Toast.LENGTH_SHORT).show()
            }
        }
        loginOnlineB!!.setOnClickListener {
            if (!DataCenter.Companion.LoginScreen.lockLoginOnline) {
                DataCenter.Companion.LoginScreen.lockLoginOnline = true
                var intent = Intent()
                intent.setClass(this, onlineLogin::class.java)
                startActivity(intent)
            } else {
                Toast.makeText(baseContext, "正在连接，请勿重复单击", Toast.LENGTH_SHORT).show()
            }
        }
    }

    fun testConnection() {
        val cm = baseContext.getSystemService(Context.CONNECTIVITY_SERVICE) as ConnectivityManager

        val networkInfo = cm.activeNetworkInfo

        if (networkInfo != null && networkInfo.isConnected) {
            //Whether you are connected with the internet

            if (networkInfo.type == ConnectivityManager.TYPE_WIFI) {
                //TODO：WIFI连接
            }

            if (networkInfo.type == ConnectivityManager.TYPE_MOBILE) {
                //TODO：蜂窝数据连接
            }
        }
    }

    override fun onCreateOptionsMenu(menu: Menu): Boolean {
        // Inflate the menu; this adds items to the action bar if it is present.
        menuInflater.inflate(R.menu.menu_main, menu)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        return when (item.itemId) {
            R.id.action_settings -> true
            else -> super.onOptionsItemSelected(item)
        }
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {

        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }
}
