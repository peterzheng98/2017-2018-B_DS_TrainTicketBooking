package group.peterzheng.trainticketbookingsystem.feature

import android.os.Bundle
import android.support.design.widget.Snackbar
import android.support.v7.app.AppCompatActivity
import android.view.Menu
import android.view.MenuItem
import android.widget.Button
import android.widget.ProgressBar
import android.widget.TextView

import kotlinx.android.synthetic.main.activity_main.*
import kotlinx.android.synthetic.main.content_main.*

class MainActivity : AppCompatActivity() {
    var ipAddressT : TextView? = null
    var ipPortT : TextView? = null
    var testConnB : Button? = null
    var loginOfflineB : Button? = null
    var loginOnlineB : Button? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        setSupportActionBar(toolbar)

        fab.setOnClickListener { view ->
            Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
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
    fun initView(){
        ipAddressT = findViewById<TextView>(R.id.ipAddr)
        ipPortT = findViewById<TextView>(R.id.ipPort)
        testConnB = findViewById<Button>(R.id.testConn)
        loginOnlineB = findViewById<Button>(R.id.loginOnline)
        loginOfflineB = findViewById<Button>(R.id.loginOffline)
        //绑定按钮监听
        loginOfflineB!!.setOnClickListener{
            textStatus.visibility = TextView.VISIBLE
            textStatus!!.setText("正在加载数据登录系统")
            testProgress.visibility = ProgressBar.VISIBLE
        }
        testConnB!!.setOnClickListener{
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
