var englishAlphabet = [
  "A",
  "B",
  "C",
  "D",
  "E",
  "F",
  "G",
  "H",
  "I",
  "J",
  "K",
  "L",
  "M",
  "N",
  "O",
  "P",
  "Q",
  "R",
  "S",
  "T",
  "U",
  "V",
  "W",
  "X",
  "Y",
  "Z"
];

var parentElement = document.querySelector(".lettergame .box");
let arry = Array.from(englishAlphabet);

arry.forEach(lettwe => {
  var spanElement = document.createElement("span");
  spanElement.classList.add("letter-box");
  let x = document.createTextNode(lettwe);
  spanElement.appendChild(x);
  parentElement.appendChild(spanElement);
});
// ------------------------------------------------------------------

// Object worde

let worde = {
  Langueg: ["javascript", "php", "python", "go", "r", "mysql"],
  Moves: ["up", "coco"],
  Peaple: ["Osama Ali", "Ali Hassen", "Ahmed", "Mohamed Sayed"],
  Countint: ["yemen", "egypt", "erag", "syrea"]
};

let keyworde = Object.keys(worde);
// keys -----------------------
let numberRandom = Math.floor(Math.random() * keyworde.length);
let numberponame = keyworde[numberRandom];
let numberprovalue = worde[numberponame];

// value -----------------------
let numberRandvalue = Math.floor(Math.random() * numberprovalue.length);

let numbervaluevalue = worde[numberponame][numberRandvalue];

let span = document.querySelector("#word-form span");
span.classList.add("boxwordrandom");
span.innerHTML = numberponame;

let parentElementspan = document.querySelector(".letrspanbox");

let wordarr = Array.from(numbervaluevalue);
wordarr.forEach(letter => {
  let sapboxleter = document.createElement("span");
  if (letter === " ") {
    sapboxleter.classList.add("has-width");
  }

  parentElementspan.appendChild(sapboxleter);
});

let allspans = document.querySelectorAll(".letrspanbox span");

let letetfalse = 0;

let letterincrement = document.querySelector(".mangame");

document.addEventListener("click", e => {
  let chekletter = false;
  if (e.target.className === "letter-box") {
    e.target.classList.add("has-width");

    let theletterclick = e.target.innerHTML.toLowerCase();

    wordarr.forEach((wordletter, WordIndex) => {
      if (theletterclick == wordletter) {
        chekletter = true;
        allspans.forEach((sapn, indesspan) => {
          if (WordIndex === indesspan) {
            sapn.innerHTML = wordletter;
            document.getElementById("scses").play();
          }
        });
      } else {
        document.getElementById("fild").play();
      }
    });
    if (chekletter !== true) {
      letetfalse++;
      letterincrement.classList.add(`rong-${letetfalse}`);
    }

    if (letetfalse === 7) {
      let cretdivmain = document.createElement("div");
      cretdivmain.classList.add("bacend");

      let cretdiv = document.createElement("div");
      cretdiv.classList.add("end");
      let cretspan = document.createElement("span");
      let textspan = document.createTextNode(`🫤 لقد خسرت `);
      cretspan.appendChild(textspan);
      cretdiv.appendChild(cretspan);
      cretdivmain.appendChild(cretdiv);
      document.body.appendChild(cretdivmain);
      setTimeout(() => {
        cretdivmain.remove();
        location.reload();
      }, 2000);
    } else {
      if (numbervaluevalue.length === length) {
        location.reload();
      }
    }
  }
});
