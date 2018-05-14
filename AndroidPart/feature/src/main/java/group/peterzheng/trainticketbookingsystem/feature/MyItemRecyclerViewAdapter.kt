package group.peterzheng.trainticketbookingsystem.feature

import android.support.v7.widget.RecyclerView
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView


import group.peterzheng.trainticketbookingsystem.feature.dummy.DummyContent.DummyItem

import kotlinx.android.synthetic.main.fragment_item.view.*
import kotlinx.android.synthetic.main.fragment_item_list.view.*
import java.util.*

/**
 * [RecyclerView.Adapter] that can display a [DummyItem] and makes a call to the
 * specified [OnListFragmentInteractionListener].
 * TODO: Replace the implementation with code for your data type.
 */
data class TrainTicketInformation(
        val TrainID : String,
        val Place : Pair<String, String>,
        val StartAndFinishTime : Pair<Date, Date>,
        val TicketRemain : Array<Pair<String, Int> >
)

class TicketAdapter(val items : List<TrainTicketInformation>, val itemClickListener: (TrainTicketInformation) -> Unit) : RecyclerView.Adapter<TicketAdapter.ViewHolder>(){

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val view = LayoutInflater.from(parent.context).inflate(R.layout.fragment_item_list, parent, false)
        return ViewHolder(view, itemClickListener)
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        holder.bind(items[position])
    }
    override fun getItemCount(): Int = items.size

    class ViewHolder(val view: View, val itemClickListener: (TrainTicketInformation) -> Unit) : RecyclerView.ViewHolder(view){
        fun bind(ticket : TrainTicketInformation){
            view.list.trainNumber.text = ticket.TrainID
            view.list.destPlace.text = ticket.Place.first
            view.list.arrivalPlace.text = ticket.Place.second
            view.list.arrivalTime.text = ticket.StartAndFinishTime.second.toString()
            view.list.departTime.text = ticket.StartAndFinishTime.first.toString()
            view.list.ticketLevel1.text = (ticket.TicketRemain[0].first + ": " + ticket.TicketRemain[0].second)
            view.list.ticketLevel2.text = (ticket.TicketRemain[1].first + ": " + ticket.TicketRemain[1].second)
            view.list.ticketLevel3.text = (ticket.TicketRemain[2].first + ": " + ticket.TicketRemain[2].second)
            view.setOnClickListener{
                itemClickListener(ticket)
            }
        }
    }
}