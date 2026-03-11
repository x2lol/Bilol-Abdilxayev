const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");

const SIZE = 280;
const BRUSH_RADIUS = 8;

let lastX = null;
let lastY = null;
let drawing = false;
const fingerOffsetY = -30;
const fingerOffsetX = -30;

/* mouse handlers */
canvas.addEventListener("mousedown",(e)=>{

    drawing = true;

    const rect = canvas.getBoundingClientRect();

    drawLine(
        e.clientX - rect.left,
        e.clientY - rect.top
    );

});


canvas.addEventListener("mouseleave", ()=>{
    lastX = null;
    lastY = null;
});

canvas.addEventListener("mouseup",()=>{
    drawing=false
    lastX = null;;
    lastY = null;
});
canvas.addEventListener("mousemove",(e)=>{

    if(!drawing) return;

    const rect = canvas.getBoundingClientRect();

    drawLine(
        e.clientX - rect.left,
        e.clientY - rect.top
    );

});
/* touch handler */
canvas.addEventListener("touchend",()=>{
    drawing=false;
    lastX = null;
    lastY = null;
});

canvas.addEventListener("touchstart",(e)=>{

    e.preventDefault();

    drawing = true;

    const touch = e.touches[0];
    const rect = canvas.getBoundingClientRect();

    drawLine(
        touch.clientX - rect.left + fingerOffsetX,
        touch.clientY - rect.top + fingerOffsetY
    );

});

canvas.addEventListener("touchmove",(e)=>{

    e.preventDefault();

    if(!drawing) return;

    const touch = e.touches[0];
    const rect = canvas.getBoundingClientRect();

    drawLine(
        touch.clientX - rect.left + fingerOffsetX,
        touch.clientY - rect.top + fingerOffsetY
    );

});

function drawPoint(x, y) {

    const gradient = ctx.createRadialGradient(
        x, y, 0,
        x, y, BRUSH_RADIUS
    );

    gradient.addColorStop(0, "rgba(255,255,255,1)");
    gradient.addColorStop(0.4, "rgba(255,255,255,0.6)");
    gradient.addColorStop(1, "rgba(255,255,255,0)");

    ctx.fillStyle = gradient;

    ctx.beginPath();
    ctx.arc(x, y, BRUSH_RADIUS, 0, Math.PI * 2);
    ctx.fill();
}

function drawLine(x, y) {
    ctx.globalCompositeOperation = "lighter";

    if (lastX === null) {

        drawPoint(x, y);
        lastX = x;
        lastY = y;
        return;

    }

    const dx = x - lastX;
    const dy = y - lastY;

    const dist = Math.sqrt(dx*dx + dy*dy);

    const step = 5; // pixels between stamps
    const steps = Math.ceil(dist / step);

    for (let i = 0; i <= steps; i++) {

        const t = i / steps;

        const px = lastX + dx * t;
        const py = lastY + dy * t;

        drawPoint(px, py);
    }

    lastX = x;
    lastY = y;
}

function clearCanvas(){

    ctx.globalCompositeOperation = "source-over";

    ctx.clearRect(0,0,canvas.width,canvas.height);
    
    lastX = null;
    lastY = null;
}

function getCanvasPosition(clientX, clientY){

    const rect = canvas.getBoundingClientRect();

    return {
        x: clientX - rect.left,
        y: clientY - rect.top
    };

}


function extractPixels(){

    const image = ctx.getImageData(0,0,280,280);
    const data = image.data;

    let pixels = [];

    for(let i=0;i<data.length;i+=4){

        const r = data[i];
        const g = data[i+1];
        const b = data[i+2];

        const intensity = (r+g+b)/3;

        pixels.push(intensity);

    }

    return pixels;
}


