function renderPredictions(list){

const container=document.getElementById("predictions");
container.innerHTML="";

list.forEach(p=>{

const row=document.createElement("div");
row.className="prediction-bar";

const label=document.createElement("div");
label.className="prediction-label";
label.innerText=p.label;

const track=document.createElement("div");
track.className="prediction-track";

const fill=document.createElement("div");
fill.className="prediction-fill";

fill.style.width=(p.prob*100)+"%";

track.appendChild(fill);

const value=document.createElement("div");
value.className="prediction-value";
value.innerText=(p.prob*100).toFixed(1)+"%";

row.appendChild(label);
row.appendChild(track);
row.appendChild(value);

container.appendChild(row);

});

}

/* backend call */

async function sendToBackend(){

const payload={
width:28,
height:28,
pixels:grid
};

const res=await fetch("/api/recognize",{
method:"POST",
headers:{"Content-Type":"application/json"},
body:JSON.stringify(payload)
});

const data=await res.json();

renderPredictions(data.predictions);

}