package group.peterzheng.trainticketbookingsystem.feature

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.annotation.VisibleForTesting
import android.support.v4.app.FragmentManager
import android.view.View.INVISIBLE
import android.view.View.VISIBLE
import android.widget.RadioButton
import android.widget.RadioGroup
import kotlinx.android.synthetic.main.activity_control_panel.*
import kotlinx.android.synthetic.main.fragment_item.*

class ControlPanel : AppCompatActivity() {

    /*var f1 : myFragment = myFragment()
    var f2 : myFragment = myFragment()
    var f3 : myFragment = myFragment()
    var f4 : myFragment = myFragment()

    f1.doit("1")

    var F : FragmentManager ?= getSupportFragmentManager()*/

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_control_panel)


        initView()

    }

    override fun onStart() {
        super.onStart()
        bookingTicket.isChecked = true
    }

    fun initView() {

        if(DataCenter.Companion.UserState.UserLevel == 0)
        {
            trainManage.visibility = RadioButton.INVISIBLE
            userManage.visibility = RadioButton.INVISIBLE
        }

        mainButton.setOnCheckedChangeListener(object : RadioGroup.OnCheckedChangeListener {
            override fun onCheckedChanged(group: RadioGroup?, checkedId: Int) {
                when (checkedId) {
                    trainManage.id -> {
                        //TODO
                    }
                    userManage.id -> {
                        //TODO
                    }
                    bookingTicket.id -> {
                        //TODO
                    }
                    userInformation.id -> {
                        //TODO
                    }
                }
            }
        })
    }
}
