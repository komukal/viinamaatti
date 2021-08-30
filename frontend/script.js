const targetList = document.getElementById('drink-list');

function order(n){
  console.log(n);
}

function makeList(drinks){
  const list = targetList;
  for(let i = 0; i < (Math.ceil(drinks.length * 0.16)); i++){
    const page = document.createElement("DIV");
    page.classList.add("page")
    for(let j = 0; j < 6; j++){
      let index = j+i*6
      console.log(index);
      if(!drinks[index]) continue;



      const listItem = document.createElement("LI");
      listItem.innerHTML = ("<p>" + drinks[index].name + "</p>");
      const image = document.createElement("IMAGE");
      image.src = drinks[index].imagePath;
      listItem.addEventListener("click", function(){
        order(drinks[index].recipe);
      });
      listItem.append(image);
      page.append(listItem);
    }
    list.append(page)
  }
}

function init () {
  const drinks = JSON.parse(this.response);
  console.log("Hello");
  makeList(drinks.drinks);
}

var oReq = new XMLHttpRequest();
oReq.addEventListener("load", init);
oReq.open("GET", "./drinks.json");
oReq.send();
