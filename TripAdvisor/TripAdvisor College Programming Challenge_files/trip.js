function prettify(t) {
	var sec = Math.floor(t % 60);
	var min = Math.floor(t/60) % 60;
	var hr  = Math.floor(t/(60*60)) % 24;
	var day  = Math.floor(t/(60*60*24));
	if( sec < 10 ) sec = "0"+sec;
	if( hr && min < 10 ) min = "0"+min;
	if( day == 1 ) {
		hr += 24;
		return hr + ":" + min + ":" + sec;
	}
	if( day < 1 ) return hr + ":" + min + ":" + sec;
	return day + " days, " + hr + "h " + min + "min";
}

function countdown() {
	var cdwn =document.getElementById('countdown');
	if(!cdwn) return;
	var start = 1442664000;
	var close = 1442707200;
	var d = new Date();
	var tts = start - (d.getTime()/1000);
	var ttc = close - (d.getTime()/1000);
	if(ttc < 0) return;
	var isopen = false;
	var tt = tts;
	if(tt < 0) {
		isopen = true;
		tt = ttc;
	}
	var p = prettify(tt);
	if(isopen) {
		//cdwn.innerHTML = 'Ending in ' + p;
	} else {
		cdwn.innerHTML = p + ' until the challenge begins.';
	}
}

function R(s) { return s.replace(/[a-z]/g, function(c) { return String.fromCharCode( 2^ (122>=(c= c.charCodeAt(0)+13) ? c : c-26)); }); }

function r(s) { return s.replace(/[`{}a-z]/g, function(c) { return String.fromCharCode( (122>=(c= (2^c.charCodeAt(0))+13) ? c : c-26)); }); }

function cont() {
	var ct =document.getElementById('questions');
	if(!ct) return;
	ct.innerHTML = "Questions?  Contact us at ";
	var m=r("ag`vglxxtcv-rwl{{pcvp@egtalsktd`g.r`x");
	var x=r("l"); var s=r("xlt{e`"); var t=r("wgpq");
	var n = document.createElement(x);
	n.setAttribute(t, s+':'+m);
	n.innerHTML = m;
	ct.appendChild(n);
}

function selectChangeUpdateSchool(ss, em) {
	em.setAttribute('placeholder', 'user@' + (ss.value?schools[ss.value]:'example.edu'));
}

function appendListener() {
	var rf =document.getElementById('REGISTER');
	if(rf) {
		var ss = rf.elements.namedItem("school");
		var em = rf.elements.namedItem("email");
		if(ss && em) {
			ss.addEventListener("change", function() {
				selectChangeUpdateSchool(ss, em);
			}, false);
			if( window.sid && ss.selectedIndex <=0 ) {
				var options = ss.options;
				for(var i = options.length; --i >= 0 ; ) {
					var opt = options[i];
					if( opt.value == sid ) {
						ss.selectedIndex = i;
						break;
					}
				}	
			}
			selectChangeUpdateSchool(ss, em);
		}
	}
}

var refreshtab = function() {
	var st =document.getElementById('SUBTAB');
	if(!st) return;
	var ajax = new XMLHttpRequest();
	ajax.onreadystatechange = function() {
		if( this.readyState == 4 && this.status == 200 ) {
			var resp = this.response;
			var content=resp.getElementById('SUBTAB');
			if( content ) {
				st.innerHTML = content.innerHTML;
				if( content.innerHTML.indexOf('pending') >= 0 ) setTimeout("refreshtab()", 30000);
			}
		}
	}
	ajax.open("get", document.location.href, true);
	ajax.responseType = "document";
	ajax.send(null);
}

var init = function() {
	cont();
	setInterval("countdown()", 500);
	appendListener();
	var st =document.getElementById('SUBTAB');
	if( st ) {
		if( st.innerHTML.indexOf('pending') >= 0 ) setTimeout("refreshtab()", 30000);
	}
}

if(document.addEventListener)
	document.addEventListener("DOMContentLoaded", init, false);
else document.onload = init;
