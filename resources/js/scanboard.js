$(function() {
	//页面淡入效果
	$(".animsition").animsition({
		inClass: 'fade-in',
		outClass: 'fade-out',
		inDuration: 300,
		outDuration: 1000,
		// e.g. linkElement   :   'a:not([target="_blank"]):not([href^=#])'
		loading: false,
		loadingParentElement: 'body', //animsition wrapper element
		loadingClass: 'animsition-loading',
		unSupportCss: ['animation-duration',
			'-webkit-animation-duration',
			'-o-animation-duration'
		],
		//"unSupportCss" option allows you to disable the "animsition" in case the css property in the array is not supported by your browser.
		//The default setting is to disable the "animsition" in a browser that does not support "animation-duration".

		overlay: false,

		overlayClass: 'animsition-overlay-slide',
		overlayParentElement: 'body'
	});

	document.onreadystatechange = subSomething;

	function subSomething() {
		if (document.readyState == "complete") {
			$('#loader').hide();
		}
	}

	//顶部时间
	function getTime() {
		var myDate = new Date();
		var myYear = myDate.getFullYear(); //获取完整的年份(4位,1970-????)
		var myMonth = myDate.getMonth() + 1; //获取当前月份(0-11,0代表1月)
		var myToday = myDate.getDate(); //获取当前日(1-31)
		var myDay = myDate.getDay(); //获取当前星期X(0-6,0代表星期天)
		var myHour = myDate.getHours(); //获取当前小时数(0-23)
		var myMinute = myDate.getMinutes(); //获取当前分钟数(0-59)
		var mySecond = myDate.getSeconds(); //获取当前秒数(0-59)
		var week = ['星期日', '星期一', '星期二', '星期三', '星期四', '星期五', '星期六'];
		var nowTime;

		nowTime = myYear + '-' + fillZero(myMonth) + '-' + fillZero(myToday) + '&nbsp;&nbsp;' + week[myDay] + '&nbsp;&nbsp;' + fillZero(myHour) + ':' + fillZero(myMinute) + ':' + fillZero(mySecond);
		$('.topTime').html(nowTime);
	};

	function fillZero(str) {
		var realNum;
		if (str < 10) {
			realNum = '0' + str;
		} else {
			realNum = str;
		}
		return realNum;
	}
	setInterval(getTime, 1000);

	function totalNum(obj, speed) {
		var singalNum = 0;
		var timer;
		var totalNum = obj.attr('total');

		if (totalNum) {
			timer = setInterval(function() {
				singalNum += speed;
				if (singalNum >= totalNum) {
					singalNum = totalNum;
					clearInterval(timer);
				}
				obj.html(singalNum);
			}, 1);
		}
	}

	//高德地图
	var myMap = new AMap.Map('myMap', {
		resizeEnable: true,
		zoom: 14,
		mapStyle: 'amap://styles/darkblue',
		center: [103.752171, 36.068716],
	});

	var point = [
		[103.752171, 36.068716],
		[103.759037, 36.072046],
		[103.73788, 36.061257]
	]
	var maker;
	for (var i = 0; i < point.length; i += 1) {
		var marker = new AMap.Marker({
			position: point[i],
			map: myMap,
			icon: '../resources/images/images/s_ico4.jpg',
		});
		marker.content = '<p>ZC1712120023</p>' +
			'<p>起点：配件A厂</p>' +
			'<p>终点：美的冰箱公司</p>' +
			'<p>满载率：95%</p>' +
			'<p>已使用时间：2小时15分</p>';
		marker.on('click', markerClick);
		//map.setFitView(); 
	}
	var infoWindow = new AMap.InfoWindow({
		offset: new AMap.Pixel(16, -36)
	});

	function markerClick(e) {
		infoWindow.setContent(e.target.content);
		infoWindow.open(myMap, e.target.getPosition());
	}
	myMap.on('click', function() {
		infoWindow.close();
	});


	//统计图
	var myChart1 = echarts.init(document.getElementById('myChart1'));
	var option1 = {
		legend: {
			data: ['下料总量', '计划下料总量', '额外下料总量', '计划下水', '已下水', '已下拌料水量', '已下洗槽水量'],
			textStyle: {
				color: '#fff'
			},
			type: 'scroll',
			pageIconColor: '#fff',
			pageTextStyle: {
				color: '#fff'
			},
			selected: {
				'下料总量': true,
				'计划下料总量': true,
				'额外下料总量': true,
				'计划下水': false,
				'已下水': false,
				'已下拌料水量': false,
				'已下洗槽水量': false
			}
		},
		tooltip: {
			trigger: 'item',
			formatter: function(params) {
				var res = '本月' + params.name + '号运单数：' + params.data;
				return res;
			}
		},
		grid: {
			top: '21%',
			left: '1%',
			width: '97%',
			height: '75%',
			containLabel: true
		},
		xAxis: {
			data: ['1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18', '19', '20', '21', '22', '23', '24', '25', '26', '27', '28', '29', '30', '31'],
			axisLabel: {
				show: true,
				textStyle: {
					fontSize: '12px',
					color: '#fff',
				}
			},
			axisLine: {
				lineStyle: {
					color: '#fff',
					width: 1,
				}
			}
		},

		yAxis: [{
			// name: '下料总量/计划下料总量/额外下料总量',
			// nameTextStyle: {
			// 	padding: [0, 0, 0, 150]
			// },
			axisLabel: {
				show: true,
				textStyle: {
					fontSize: '12px',
					color: '#fff',
				}
			},
			axisLine: {
				lineStyle: {
					color: '#fff',
					width: 1,
				}
			},
			splitLine: {
				show: false,
			}
		}, {
			// name: '计划用水/已下水/已下拌料水量/已下洗槽水量',
			// nameTextStyle: {
			// 	padding: [0, 170, 0, 0]
			// },
			axisLabel: {
				show: true,
				textStyle: {
					fontSize: '12px',
					color: '#fff',
				}
			},
			axisLine: {
				lineStyle: {
					color: '#fff',
					width: 1,
				}
			},
			splitLine: {
				show: false,
			}
		}],

		series: [{
			name: '下料总量',
			type: 'line',
			data: ['5', '14', '3', '6', '8', '18', '11', '4', '8', '7', '16', '13', '6', '10', '11', '9', '19', '13', '4', '20', '12', '7', '13', '15', '8', '3', '9', '16', '11', '16', '8'],
			itemStyle: {
				normal: {
					color: new echarts.graphic.LinearGradient(
						0, 0, 0, 1, [{
							offset: 0,
							color: '#fe3636'
						}, {
							offset: 1,
							color: '#fc9696'
						}]
					),
				},
			},
		}, {
			name: '计划下料总量',
			type: 'line',
			data: ['8', '14', '5', '10', '8', '18', '2', '5', '8', '7', '16', '12', '6', '10', '11', '9', '19', '17', '4', '20', '12', '7', '13', '2', '8', '3', '9', '10', '11', '11', '8'],
			itemStyle: {
				normal: {
					color: new echarts.graphic.LinearGradient(
						0, 0, 0, 1, [{
							offset: 0,
							color: '#3876cd'
						}, {
							offset: 1,
							color: '#54ffff'
						}]
					),
				},
			},
		}, {
			name: '额外下料总量',
			type: 'line',
			data: ['18', '14', '3', '10', '8', '11', '11', '8', '8', '7', '11', '20', '6', '10', '11', '9', '19', '17', '4', '20', '12', '7', '13', '2', '8', '3', '9', '10', '11', '11', '8'],
			itemStyle: {
				normal: {
					color: new echarts.graphic.LinearGradient(
						0, 0, 0, 1, [{
							offset: 0,
							color: '#3fc56e'
						}, {
							offset: 1,
							color: '#92cea7'
						}]
					),
				},
			},
		}, {
			name: '计划下水',
			type: 'line',
			yAxisIndex: 1,
			data: ['3', '14', '3', '10', '8', '18', '12', '8', '8', '7', '16', '20', '11', '10', '11', '9', '19', '17', '4', '20', '12', '7', '13', '2', '8', '3', '9', '10', '11', '11', '8'],
			itemStyle: {
				normal: {
					color: new echarts.graphic.LinearGradient(
						0, 0, 0, 1, [{
							offset: 0,
							color: '#e8ad22'
						}, {
							offset: 1,
							color: '#e2c88a'
						}]
					),
				},
			},
		}, {
			name: '已下水',
			type: 'line',
			yAxisIndex: 1,
			data: ['5', '14', '3', '10', '8', '18', '11', '8', '8', '7', '11', '20', '6', '10', '11', '9', '19', '17', '4', '20', '12', '7', '13', '2', '8', '3', '9', '10', '11', '11', '8'],
			itemStyle: {
				normal: {
					color: new echarts.graphic.LinearGradient(
						0, 0, 0, 1, [{
							offset: 0,
							color: '#392bf3'
						}, {
							offset: 1,
							color: '#9892ec'
						}]
					),
				},
			},
		}, {
			name: '已下拌料水量',
			type: 'line',
			yAxisIndex: 1,
			data: ['8', '14', '3', '10', '8', '23', '11', '8', '8', '7', '16', '21', '6', '23', '11', '9', '19', '17', '4', '20', '12', '7', '13', '2', '8', '3', '9', '10', '11', '11', '8'],
			itemStyle: {
				normal: {
					color: new echarts.graphic.LinearGradient(
						0, 0, 0, 1, [{
							offset: 0,
							color: '#ec2cdc'
						}, {
							offset: 1,
							color: '#e885e0'
						}]
					),
				},
			},
		}, {
			name: '已下洗槽水量',
			type: 'line',
			yAxisIndex: 1,
			data: ['8', '14', '3', '10', '5', '18', '11', '8', '8', '4', '16', '20', '6', '10', '24', '9', '19', '17', '4', '20', '12', '7', '13', '2', '8', '3', '9', '10', '11', '11', '8'],
			itemStyle: {
				normal: {
					color: new echarts.graphic.LinearGradient(
						0, 0, 0, 1, [{
							offset: 0,
							color: '#27efaf'
						}, {
							offset: 1,
							color: '#8ff5d4'
						}]
					),
				},
			},
		}],
	}

	//运单状态文字滚动
	$('#FontScroll').FontScroll({
		time: 3000,
		num: 1
	});

	setTimeout(function() {

		$('.progress').each(function(i, ele) {
			var PG = $(ele).attr('progress');
			var trend = $(ele).attr('trend');
			var PGNum = parseInt(PG);
			var zero = 0;
			var speed = 50;
			var timer;

			$(ele).find('h4').html(zero + '%');
			if (trend === 'up') {
				$(ele).find('img').attr('src', '../resources/images/images/arrow_up.png');
			} else {
				$(ele).find('img').attr('src', '../resources/images/arrow_down.png');
			}
			if (PGNum < 10) {
				$(ele).find('.progressBar span').addClass('bg-red');
				$(ele).find('h3 i').addClass('color-red');
			} else if (PGNum >= 10 && PGNum < 50) {
				$(ele).find('.progressBar span').addClass('bg-yellow');
				$(ele).find('h3 i').addClass('color-yellow');
			} else if (PGNum >= 50 && PGNum < 100) {
				$(ele).find('.progressBar span').addClass('bg-blue');
				$(ele).find('h3 i').addClass('color-blue');
			} else {
				$(ele).find('.progressBar span').addClass('bg-green');
				$(ele).find('h3 i').addClass('color-green');
			}
			$(ele).find('.progressBar span').animate({
				width: PG
			}, PGNum * speed);
			timer = setInterval(function() {
				zero++;
				$(ele).find('h4').html(zero + '%');
				if (zero == PGNum) {
					clearInterval(timer);
				}
			}, speed);
		});



		//基本信息
		totalNum($('#indicator1'), 1);
		totalNum($('#indicator2'), 1);
		totalNum($('#indicator3'), 1);

		//总计运单数
		totalNum($('#totalNum'), 1000);

		myChart1.setOption(option1);

	}, 500);

	//弹窗
	$('.summaryBtn').on('click', function() {
		$('.filterbg').show();
		$('.popup').show();
		$('.popup').width('3px');
		$('.popup').animate({
			height: '76%'
		}, 400, function() {
			$('.popup').animate({
				width: '82%'
			}, 400);
		});
		setTimeout(summaryShow, 800);
	});
	$('.popupClose').on('click', function() {
		$('.popupClose').css('display', 'none');
		$('.errorSummary').hide();
		$('.popup').animate({
			width: '3px'
		}, 400, function() {
			$('.popup').animate({
				height: 0
			}, 400);
		});
		setTimeout(summaryHide, 800);
	});

	function summaryShow() {
		$('.popupClose').css('display', 'block');
		$('.errorSummary').show();

	};

	function summaryHide() {
		$('.filterbg').hide();
		$('.popup').hide();
		$('.popup').width(0);
	};

	$(window).resize(function() {
		myChart1.resize();
		try {
			myChart2.resize();
		} catch (err) {
			return false;
		}
	});



	/***************2018-01-03增加js****************/

	//地图上的搜索
	$('.searchBtn').on('click', function() {
		$(this).hide();
		$('.searchInner').addClass('open');
		setTimeout(function() {
			$('.searchInner').find('form').show();
		}, 400);
	});

	$('.search').on('click', function(event) {
		event.stopPropagation();
	});
	$('body').on('click', function() {
		$('.searchInner').find('form').hide();
		$('.searchInner').removeClass('open');
		setTimeout(function() {
			$('.searchBtn').show();
		}, 400);
	});

	//车辆状态滚动条样式
	$('.stateUl').niceScroll({
		cursorcolor: "#045978", //#CC0071 光标颜色
		cursoropacitymax: 0.6, //改变不透明度非常光标处于活动状态（scrollabar“可见”状态），范围从1到0
		touchbehavior: false, //使光标拖动滚动像在台式电脑触摸设备
		cursorwidth: "4px", //像素光标的宽度
		cursorborder: "0", // 	游标边框css定义
		cursorborderradius: "4px", //以像素为光标边界半径
		autohidemode: false //是否隐藏滚动条
	});


	//车辆信息工作时间表
	//模拟数据
	var carData = [{
		dateLable: "2018-01-01 星期一",
		data: {
			workTime: [{
				start: "07:30",
				end: "13:15"
			}, {
				start: "14:40",
				end: "21:50"
			}],
			standard: [{
				start: "00:00",
				end: "05:00"
			}, {
				start: "08:00",
				end: "12:00"
			}, {
				start: "14:00",
				end: "19:00"
			}]
		}
	}, {
		dateLable: "2018-01-02 星期二",
		data: {
			workTime: [{
				start: "03:10",
				end: "09:40"
			}],
			standard: [{
				start: "00:00",
				end: "05:00"
			}, {
				start: "08:00",
				end: "12:00"
			}, {
				start: "14:00",
				end: "19:00"
			}]
		}
	}, {
		dateLable: "2018-01-03 星期三",
		data: {
			workTime: [{
				start: "06:15",
				end: "14:08"
			}, {
				start: "15:53",
				end: "24:00"
			}],
			standard: [{
				start: "00:00",
				end: "05:00"
			}, {
				start: "08:00",
				end: "12:00"
			}, {
				start: "14:00",
				end: "19:00"
			}]
		}
	}, {
		dateLable: "2018-01-04 星期四",
		data: {
			workTime: [{
				start: "00:00",
				end: "07:32"
			}, {
				start: "12:20",
				end: "19:50"
			}],
			standard: [{
				start: "00:00",
				end: "05:00"
			}, {
				start: "08:00",
				end: "12:00"
			}, {
				start: "14:00",
				end: "19:00"
			}]
		}
	}, {
		dateLable: "2018-01-05 星期五",
		data: {
			workTime: [{
				start: "06:15",
				end: "17:20"
			}],
			standard: [{
				start: "00:00",
				end: "05:00"
			}, {
				start: "08:00",
				end: "12:00"
			}, {
				start: "14:00",
				end: "19:00"
			}]
		}
	}, {
		dateLable: "2018-01-06 星期六",
		data: {
			workTime: [{
				start: "14:40",
				end: "22:38"
			}],
			standard: [{
				start: "00:00",
				end: "05:00"
			}, {
				start: "08:00",
				end: "12:00"
			}, {
				start: "14:00",
				end: "19:00"
			}]
		}
	}, {
		dateLable: "2018-01-07 星期天",
		data: {
			workTime: [{
				start: "06:30",
				end: "12:20"
			}, {
				start: "14:25",
				end: "20:33"
			}],
			standard: [{
				start: "00:00",
				end: "05:00"
			}, {
				start: "08:00",
				end: "12:00"
			}, {
				start: "14:00",
				end: "19:00"
			}]
		}
	}];

	function Schedule() {
		var Item = $('.dataBox');
		var Size = Item.eq(0).width();
		var oDay = 24 * 60;

		function getMin(timeStr) {
			var timeArray = timeStr.split(":");
			var Min = parseInt(timeArray[0]) * 60 + parseInt(timeArray[1]);
			return Min;
		}

		//在时间轴上添加工作时间数据
		Item.each(function(i, ele) {
			var ItemData = carData[i];

			function addData(obj, dataParam) {
				for (var j = 0; j < dataParam.length; j++) {
					var pos, wid, workCeil, sDate, sStart, sEnd, sConsume;
					pos = getMin(dataParam[j].start) / oDay * 100 + '%';
					wid = (getMin(dataParam[j].end) - getMin(dataParam[j].start)) / oDay * 100 + '%';
					sDate = ItemData.dateLable;
					sStart = dataParam[j].start;
					sEnd = dataParam[j].end;
					sConsume = getMin(dataParam[j].end) - getMin(dataParam[j].start);
					workCeil = '<span style="width: ' + wid + ';left: ' + pos + '" sDate="' + sDate + '" sStart="' + sStart + '" sEnd="' + sEnd + '" sConsume="' + sConsume + '"></span>';
					obj.append(workCeil);
				}
			}
			addData($(ele).find('.workTime'), ItemData.data.workTime);
			addData($(ele).find('.standard'), ItemData.data.standard);
		});

		//添加总用时与总单数
		var Total = $('.totalItem');
		Total.each(function(i, ele) {
			var ItemData = carData[i].data.workTime;
			var timeUsed = 0;
			for (var j = 0; j < ItemData.length; j++) {
				timeUsed += getMin(ItemData[j].end) - getMin(ItemData[j].start);
			}
			var realHour = Math.floor(timeUsed / 60);
			$(ele).find('span').eq(0).html(realHour + ':' + (timeUsed - realHour * 60));
			$(ele).find('span').eq(1).html(ItemData.length + '/' + ItemData.length);
		});
	};
	Schedule();

	//鼠标移入运单显示信息框
	$('.workTime').on('mouseenter', 'span', function(ev) {
		var x = ev.clientX;
		var y = ev.clientY;
		var sDate, sStart, sEnd, sConsume, infos, sHour, sMin;
		sDate = $(this).attr("sDate");
		sStart = $(this).attr("sStart");
		sEnd = $(this).attr("sEnd");
		sConsume = $(this).attr("sConsume");
		sHour = Math.floor(sConsume / 60);
		sMin = sConsume - sHour * 60;

		infos = '<div class="workTimeInfo" style="left:' + x + 'px;top:' + y + 'px"><p>日期：' + sDate + '</p><p>开始时间：' + sStart + '</p><p>结束时间：' + sEnd + '</p><p>总用时：' + sHour + '小时' + sMin + '分钟</p></div>';
		$('body').append(infos);
	});
	$('.workTime').on('mouseout', function() {
		$('.workTimeInfo').remove();
	});

	//车辆信息弹出框的显示隐藏效果
	$('.infoBtn').on('click', function() {
		$('.filterbg').show();
		$('.equipInfo').show();
		$('.equipInfo').width('3px');
		$('.equipInfo').animate({
			height: '76%'
		}, 400, function() {
			$('.equipInfo').animate({
				width: '82%'
			}, 400);
		});
		setTimeout(function() {
			$('.infoBox').show();
			$('.equipClose').css('display', 'block');

			setLineChart();
		}, 800);

	});

	var myChart2;

	function setLineChart() {
		myChart2 = echarts.init(document.getElementById('myChart2'), null, {
			renderer: 'svg'
		});
		var option2 = {
			tooltip: {
				trigger: 'axis',
				axisPointer: {
					type: 'shadow'
				}
			},
			legend: {
				data: ['计划下料', '已下料', '计划下水', '已下水'],
				textStyle: {
					color: '#fff'
				},
				selected: {
					'计划下水': false,
					'已下水': false
				}
			},
			grid: {
				top: '13%',
				left: '0%',
				right: '0%',
				bottom: '0%',
				containLabel: true
			},
			xAxis: {
				type: 'category',
				data: ['第一餐', '第二餐', '第三餐', '第四餐', '第五餐', '第六餐', '第七餐'],
				axisLabel: {
					show: true,
					textStyle: {
						color: '#fff',
					},
				},
				axisLine: {
					lineStyle: {
						color: '#fff',
						width: 1,
					}
				},
				splitLine: {
					show: false,
					lineStyle: {
						color: ['#eaeaea'],
						width: 0.5
					}
				}
			},
			yAxis: {
				name: '重量/水量',
				type: 'value',
				axisLabel: {
					show: true,
					textStyle: {
						color: '#fff',
					}
				},
				axisLine: {
					lineStyle: {
						color: '#fff',
						width: 1,
					}
				},
				splitLine: {
					show: true,
					lineStyle: {
						color: ['#6585ad'],
						width: 0.5
					}
				}
			},
			series: [{
				name: '计划下料',
				type: 'line',
				data: [20, 40, 60, 20, 50, 90, 10],
				areaStyle: {
					normal: {
						color: 'rgba(239, 139, 140, 0.3)',
					}
				},
				itemStyle: {
					normal: {
						color: new echarts.graphic.LinearGradient(
							0, 0, 0, 1, [{
								offset: 0,
								color: '#fe3636'
							}, {
								offset: 1,
								color: '#fc9696'
							}]
						),
					},
				}
			}, {
				name: '已下料',
				type: 'line',
				data: [30, 70, 10, 50, 40, 30, 50],
				areaStyle: {
					normal: {
						color: 'rgba(148, 186, 234, 0.3)',
					}
				},
				itemStyle: {
					normal: {
						color: new echarts.graphic.LinearGradient(
							0, 0, 0, 1, [{
								offset: 0,
								color: '#3876cd'
							}, {
								offset: 1,
								color: '#54ffff'
							}]
						),
					},
				}
			}, {
				name: '计划下水',
				type: 'line',
				data: [11, 40, 43, 67, 34, 6, 77],
				areaStyle: {
					normal: {
						color: 'rgba(157, 226, 183, 0.3)',
					}
				},
				itemStyle: {
					normal: {
						color: new echarts.graphic.LinearGradient(
							0, 0, 0, 1, [{
								offset: 0,
								color: '#3fc56e'
							}, {
								offset: 1,
								color: '#92cea7'
							}]
						),
					},
				}
			}, {
				name: '已下水',
				type: 'line',
				data: [11, 43, 23, 4, 65, 65, 42],
				areaStyle: {
					normal: {
						color: 'rgba(232, 151, 227, 0.3)',
					}
				},
				itemStyle: {
					normal: {
						color: new echarts.graphic.LinearGradient(
							0, 0, 0, 1, [{
								offset: 0,
								color: '#ec2cdc'
							}, {
								offset: 1,
								color: '#e885e0'
							}]
						),
					},
				}
			}]
		};

		myChart2.setOption(option2);
	}

	$('.equipClose').on('click', function() {
		myChart2.clear();
		$('.equipClose').css('display', 'none');
		$('.infoBox').hide();

		$('.equipInfo').animate({
			width: '3px'
		}, 400, function() {
			$('.equipInfo').animate({
				height: 0
			}, 400);
		});
		setTimeout(function() {
			$('.filterbg').hide();
			$('.equipInfo').hide();
			$('.equipInfo').width(0);
		}, 800);

	});

	var lists = [{
		value: 'zhinan',
		label: '指南',
		children: [{
			value: 'shejiyuanze',
			label: '设计原则设计原则设计原则设计原则',
			children: [{
				value: 'yizhi',
				label: '一致'
			}, {
				value: 'fankui',
				label: '反馈'
			}, {
				value: 'xiaolv',
				label: '效率'
			}, {
				value: 'kekong',
				label: '可控'
			}]
		}, {
			value: 'daohang',
			label: '导航',
			children: [{
				value: 'cexiangdaohang',
				label: '侧向导航'
			}, {
				value: 'dingbudaohang',
				label: '顶部导航'
			}]
		}]
	}, {
		value: 'zujian',
		label: '组件',
		children: [{
			value: 'basic',
			label: 'Basic',
			children: [{
				value: 'layout',
				label: 'Layout 布局'
			}, {
				value: 'color',
				label: 'Color 色彩'
			}, {
				value: 'typography',
				label: 'Typography 字体'
			}, {
				value: 'icon',
				label: 'Icon 图标'
			}, {
				value: 'button',
				label: 'Button 按钮'
			}]
		}, {
			value: 'form',
			label: 'Form',
			children: [{
				value: 'radio',
				label: 'Radio 单选框'
			}, {
				value: 'checkbox',
				label: 'Checkbox 多选框'
			}, {
				value: 'input',
				label: 'Input 输入框'
			}, {
				value: 'input-number',
				label: 'InputNumber 计数器'
			}, {
				value: 'select',
				label: 'Select 选择器'
			}, {
				value: 'cascader',
				label: 'Cascader 级联选择器'
			}, {
				value: 'switch',
				label: 'Switch 开关'
			}, {
				value: 'slider',
				label: 'Slider 滑块'
			}, {
				value: 'time-picker',
				label: 'TimePicker 时间选择器'
			}, {
				value: 'date-picker',
				label: 'DatePicker 日期选择器'
			}, {
				value: 'datetime-picker',
				label: 'DateTimePicker 日期时间选择器'
			}, {
				value: 'upload',
				label: 'Upload 上传'
			}, {
				value: 'rate',
				label: 'Rate 评分'
			}, {
				value: 'form sheet',
				label: 'Form 表单'
			}]
		}, {
			value: 'data',
			label: 'Data',
			children: [{
				value: 'table',
				label: 'Table 表格'
			}, {
				value: 'tag',
				label: 'Tag 标签'
			}, {
				value: 'progress',
				label: 'Progress 进度条'
			}, {
				value: 'tree',
				label: 'Tree 树形控件'
			}, {
				value: 'pagination',
				label: 'Pagination 分页'
			}, {
				value: 'badge',
				label: 'Badge 标记'
			}]
		}, {
			value: 'notice',
			label: 'Notice',
			children: [{
				value: 'alert',
				label: 'Alert 警告'
			}, {
				value: 'loading',
				label: 'Loading 加载'
			}, {
				value: 'message',
				label: 'Message 消息提示'
			}, {
				value: 'message-box',
				label: 'MessageBox 弹框'
			}, {
				value: 'notification',
				label: 'Notification 通知'
			}]
		}, {
			value: 'navigation',
			label: 'Navigation',
			children: [{
				value: 'menu',
				label: 'NavMenu 导航菜单'
			}, {
				value: 'tabs',
				label: 'Tabs 标签页'
			}, {
				value: 'breadcrumb',
				label: 'Breadcrumb 面包屑'
			}, {
				value: 'dropdown',
				label: 'Dropdown 下拉菜单'
			}, {
				value: 'steps',
				label: 'Steps 步骤条'
			}]
		}, {
			value: 'others',
			label: 'Others',
			children: [{
				value: 'dialog',
				label: 'Dialog 对话框'
			}, {
				value: 'tooltip',
				label: 'Tooltip 文字提示'
			}, {
				value: 'popover',
				label: 'Popover 弹出框'
			}, {
				value: 'card',
				label: 'Card 卡片'
			}, {
				value: 'carousel',
				label: 'Carousel 走马灯'
			}, {
				value: 'collapse',
				label: 'Collapse 折叠面板'
			}]
		}]
	}, {
		value: 'ziyuan',
		label: '资源',
		children: [{
			value: 'axure',
			label: 'Axure Components'
		}, {
			value: 'sketch',
			label: 'Sketch Templates'
		}, {
			value: 'jiaohu',
			label: '组件交互文档'
		}]
	}, {
		"value": 1,
		label: 'xxx'
	}, ]


	$('#cascaderbox').cascader({
		data: lists
	});

	// $.ajax({
	// 	type: "POST",
	// 	url: "http://101.132.130.199:8080/SCAUSB/System/getFeedingData",
	// 	data: {
	// 		gatewayId: 1
	// 	},
	// 	success: function(result) {
	// 		console.log(result);
	// 	},
	// 	error: function(e) {

	// 	}
	// });
});