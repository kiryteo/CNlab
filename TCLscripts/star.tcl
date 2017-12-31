set ns [new Simulator]

$ns color 1 Blue
$ns color 2 Red
$ns color 3 Green

set nf [open ot.nam w]
$ns namtrace-all $nf

set nf1 [open ot1.tr w]
$ns trace-all $nf1

proc finish {} {
    global ns nf
    $ns flush-trace
    close $nf
    exec nam ot.nam &
    exit 0
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]

$ns duplex-link $n1 $n0 2Mb 10ms DropTail
$ns duplex-link $n2 $n0 2Mb 10ms DropTail
$ns duplex-link $n4 $n0 2Mb 10ms DropTail
$ns duplex-link $n3 $n0 2Mb 10ms DropTail
$ns duplex-link $n5 $n0 2Mb 10ms DropTail
$ns duplex-link $n6 $n0 2Mb 10ms DropTail

#$ns queue-limit $n1 $n2 10
#$ns queue-limit $n3 $n4 10
#$ns queue-limit $n5 $n6 10

$ns duplex-link-op $n0 $n1 orient right
$ns duplex-link-op $n0 $n2 orient right-down
$ns duplex-link-op $n0 $n3 orient down
$ns duplex-link-op $n0 $n4 orient left-down
$ns duplex-link-op $n0 $n5 orient left
$ns duplex-link-op $n0 $n6 orient up

set tcp1 [new Agent/TCP]
$ns attach-agent $n1 $tcp1
set sink1 [new Agent/TCPSink]
$ns attach-agent $n2 $sink1
$ns connect $tcp1 $sink1

set tcp2 [new Agent/TCP]
$ns attach-agent $n3 $tcp2
set sink2 [new Agent/TCPSink]
$ns attach-agent $n4 $sink2
$ns connect $tcp2 $sink2

set tcp3 [new Agent/TCP]
$ns attach-agent $n5 $tcp3
set sink3 [new Agent/TCP]
$ns attach-agent $n6 $sink3
$ns connect $tcp3 $sink3

set ftp1 [new Application/FTP]
$ftp1 attach-agent $tcp1
$ftp1 set type_ FTP

set ftp2 [new Application/FTP]
$ftp2 attach-agent $tcp2
$ftp2 set type_ FTP

set ftp3 [new Application/FTP]
$ftp3 attach-agent $tcp3
$ftp3 set type_ FTP

$ns at 0.2 "$ftp1 start"
$ns at 0.6 "$ftp1 stop"
$ns at 0.4 "$ftp2 start"
$ns at 1.4 "$ftp2 stop"
$ns at 0.6 "$ftp3 start"
$ns at 1.8 "$ftp3 stop"

$ns at 3.0 "finish"

$ns run
