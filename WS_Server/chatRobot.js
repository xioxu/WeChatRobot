const r2 = require('r2')

async function chat(appId,msg){
    let rst = await r2.get(`http://api.qingyunke.com/api.php?key=free&appid=${appId}&msg=${msg}`).json;
     
    return rst;
}


exports.chat = chat