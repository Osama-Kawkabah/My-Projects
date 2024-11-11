let start = (document.querySelector(".boxname .start").onclick = function() {
  let namePl = prompt("What is Your Name");
  if (namePl === "" || namePl === null) {
    document.querySelector(".name span").innerHTML = "UnKnown";
  } else {
    document.querySelector(".name span").innerHTML = namePl;
  }
  document.querySelector(".boxname").remove();
});
let count = 1000;
let boxroted = document.querySelector(".boximg");
let boxes = Array.from(boxroted.children);

// let orderRang1 = [...boxes.keys()];
// console.log(orderRang1);

// let orderRang = [...Array(boxes.length).keys()];
let orderRang = Array.from(Array(boxes.length).keys());
shafel(orderRang);

boxes.forEach((box, i) => {
  // box.style.order = Math.floor(Math.random(orderRang[i]));
  box.style.order = orderRang[i];
  box.addEventListener("click", function() {
    SelSelectclasscla(box);
  });
});

function SelSelectclasscla(Selcla) {
  Selcla.classList.add("mov");

  let allbox = boxes.filter(abox => abox.classList.contains("mov"));

  if (allbox.length === 2) {
    stopclic();
    checkMathblock(allbox[0], allbox[1]);
  }
}

// -------------------
function stopclic() {
  boxroted.classList.add("stopclick");

  setTimeout(() => {
    boxroted.classList.remove("stopclick");
  }, count);
}
// -------------------
function checkMathblock(fristblock, lastblock) {
  let spancouent = document.querySelector(".tries span");
  if (fristblock.dataset.technology === lastblock.dataset.technology) {
    fristblock.classList.remove("mov");
    lastblock.classList.remove("mov");

    fristblock.classList.add("has-match");
    lastblock.classList.add("has-match");
    document.getElementById("scses").play();
  } else {
    spancouent.innerHTML = parseInt(spancouent.innerHTML) + 1;

    setTimeout(() => {
      fristblock.classList.remove("mov");
      lastblock.classList.remove("mov");
    }, count);
    let music = document.getElementById("fild").play();
  }
}

function shafel(array) {
  let corser = array.length,
    temp,
    randum;
  while (corser > 0) {
    randum = Math.floor(Math.random() * corser);
    corser--;

    temp = array[corser];
    array[corser] = array[randum];
    array[randum] = temp;
  }
  return array;
}
