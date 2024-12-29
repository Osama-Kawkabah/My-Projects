let iputclick = document.getElementById("but-sub");
let iputload = document.getElementById("text");
let boxbody = document.querySelector(".box-body");
// ------------------------------------
let textbody = document.querySelector(".text-body span");
let Tesks = document.querySelector("#Tesk span");
let Complet = document.querySelector("#Complet span");
let countTesks = 0;
let countComplet = 0;

// ------------------------------
window.onload = function() {
  iputload.focus();
};

iputclick.onclick = () => {
  if (iputload.value !== "") {
    let box = document.createElement("div");
    box.className = "box";
    box.classList.add(iputload.value);

    // createElement sapn .text
    let text = document.createTextNode(iputload.value);
    let spantext = document.createElement("span");
    spantext.className = "text";
    spantext.appendChild(text);

    // createElement sapn .but
    let but = document.createTextNode("Delet");
    let spanbut = document.createElement("span");
    spanbut.className = "but";
    spanbut.appendChild(but);

    // box.appendChild
    box.appendChild(spantext);
    box.appendChild(spanbut);
    boxbody.appendChild(box);
    textbody.remove();

    document.addEventListener("click", function(elem) {
      if (elem.target.classList.contains(`box ${iputload.value}`)) {
        console.log("xxxxxx");
      }
      if (elem.target.classList.contains("text")) {
        elem.target.classList.toggle("checed");
        Complet += 1;
      }
    });

    // -----------------------------

    Tesks.classList.add("Tesks");
    Tesks.innerHTML = countTesks += 1;
    spanbut.onclick = () => {
      box.remove();
      Tesks.innerHTML = countTesks -= 1;
    };

    // ------------------------------
    iputload.value = "";
  } else {
    textbody.style.color = "red";
  }
};

