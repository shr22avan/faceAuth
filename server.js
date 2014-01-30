var fs=require('fs');
var exec=require('child_process').exec;
var http=require('http');
var express=require('express');
var app=express();
var index=fs.readFile(__dirname+'/index.html',function(err,data){
    if(err)
    {
	console.log("Error Loading Index "+err);
	return;
    }
});
app.get('/',function(req,res){
    console.log(req.url);
    fs.readFile(__dirname+'/index.html',function(err,data){
	if(err)
	{
	    console.log("Error Loading Index "+err);
	    return;
	}
	res.setHeader('Content-Type', 'text/html');
	res.end(data);
    });
});
app.get('/main.js',function(req,res){
    console.log(req.url);
    fs.readFile(__dirname+'/main.js',function(err,data){
	if(err)
	{
	    console.log("Error Loading Main Js "+err);
	    return;
	}
	res.setHeader('Content-Type','application/javascript');
	res.end(data);
    });
});
app.listen(3000);
console.log("Server running at 3000");
