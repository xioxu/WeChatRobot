const express = require('express')
const expressWs = require('express-ws') // 引入 WebSocket 包

const chatRobot = require("./chatRobot")

const app = express();

expressWs(app) // 将 WebSocket 服务混入 app，相当于为 app 添加 .ws 方法

app.get('/', function (req, res, next) {
  res.send('API is started!')
})

// 建立 WebSocket 服务
// 
// 第一个参数为服务路径
// 第二个参数为与前端建立连接时会调用的回调函数
//   ws 相当于建立 WebSocket 的实例
//   req 为建立连接的请求
app.ws('/wx/ws', function (ws, req) {
    console.log('Wx_ws connected')
    let clientId = req.query["clientId"];

    if(!clientId){
        let msg = "invalid clientId for WS connect";
        console.log(msg);
        ws.send(msg);
        ws.close();
        return;
    }
  
    // 使用 on 方法监听事件
    //   message 事件表示从另一段（服务端）传入的数据
    ws.on('message', async function (data) {
        try{
            let jsonObj = JSON.parse(data);
            if(jsonObj.content === "exit"){
                console.log("Got close command")
                ws.close();
                return
            }

            let rst = await chatRobot.chat(jsonObj.content);
            let reply = {
                "content":rst.content
            };

            ws.send(JSON.stringify(reply));
        }catch(e){
            console.log(e);
            ws.send("Rec: "+data);
        }
    })
  
  
    // close 事件表示客户端断开连接时执行的回调函数
    ws.on('close', function (e) {
      console.log('close connection')
    })

    ws.on('error', function(e) {
        console.log('ws error')
    });
  })
  
  const port = 8026
  app.listen(port, () => {console.log(`express server listen at http://localhost:${port}`)});