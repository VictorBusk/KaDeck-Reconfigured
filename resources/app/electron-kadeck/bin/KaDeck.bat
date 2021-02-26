@if "%DEBUG%" == "" @echo off
@rem ##########################################################################
@rem
@rem  KaDeck startup script for Windows
@rem
@rem ##########################################################################

@rem Set local scope for the variables with windows NT shell
if "%OS%"=="Windows_NT" setlocal

set DIRNAME=%~dp0
if "%DIRNAME%" == "" set DIRNAME=.
set APP_BASE_NAME=%~n0
set APP_HOME=%DIRNAME%..

@rem Add default JVM options here. You can also use JAVA_OPTS and KA_DECK_OPTS to pass JVM options to this script.
set DEFAULT_JVM_OPTS=-Djava.net.useSystemProxies=true 

goto init
if defined JAVA_HOME goto findJavaFromJavaHome

set JAVA_EXE=java.exe
%JAVA_EXE% -version >NUL 2>&1
if "%ERRORLEVEL%" == "0" goto init

echo.
echo ERROR: JAVA_HOME is not set and no 'java' command could be found in your PATH.
echo.
echo Please set the JAVA_HOME variable in your environment to match the
echo location of your Java installation.

goto fail

:findJavaFromJavaHome
set JAVA_HOME=%JAVA_HOME:"=%
set JAVA_EXE=%JAVA_HOME%/bin/java.exe

if exist "%JAVA_EXE%" goto init

echo.
echo ERROR: JAVA_HOME is set to an invalid directory: %JAVA_HOME%
echo.
echo Please set the JAVA_HOME variable in your environment to match the
echo location of your Java installation.

goto fail

:init
@rem Get command-line arguments, handling Windows variants

if not "%OS%" == "Windows_NT" goto win9xME_args

:win9xME_args
@rem Slurp the command line arguments.
set CMD_LINE_ARGS=
set _SKIP=2

:win9xME_args_slurp
if "x%~1" == "x" goto execute

set CMD_LINE_ARGS=%*

:execute
cd %APP_HOME%

set CLASSPATH=lib\KaDeck-3.0.1.jar;lib\common-config-5.5.0.jar;lib\common-utils-5.5.0.jar;lib\kafka-avro-serializer-5.5.0.jar;lib\kafka-connect-avro-converter-5.5.0.jar;lib\kafka-schema-registry-5.5.0.jar;lib\kafka-schema-registry-client-5.5.0.jar;lib\kafka-schema-serializer-5.5.0.jar;lib\rest-utils-5.5.0.jar;lib\helidon-webserver-tyrus-2.0.1.jar;lib\helidon-health-checks-2.0.1.jar;lib\helidon-health-2.0.1.jar;lib\helidon-metrics-2.0.1.jar;lib\helidon-webserver-cors-2.0.1.jar;lib\helidon-webserver-2.0.1.jar;lib\helidon-media-jsonp-2.0.1.jar;lib\helidon-security-integration-webserver-2.0.1.jar;lib\helidon-security-integration-common-2.0.1.jar;lib\helidon-security-providers-jwt-2.0.1.jar;lib\helidon-security-providers-common-2.0.1.jar;lib\helidon-security-2.0.1.jar;lib\helidon-media-jsonb-2.0.1.jar;lib\helidon-media-common-2.0.1.jar;lib\helidon-tracing-config-2.0.1.jar;lib\helidon-common-key-util-2.0.1.jar;lib\helidon-security-jwt-2.0.1.jar;lib\helidon-common-configurable-2.0.1.jar;lib\helidon-security-util-2.0.1.jar;lib\helidon-config-mp-2.0.1.jar;lib\helidon-config-2.0.1.jar;lib\graal-sdk-1.0.0-rc7.jar;lib\js-20.2.0.jar;lib\regex-20.2.0.jar;lib\truffle-api-20.2.0.jar;lib\js-scriptengine-20.2.0.jar;lib\spring-security-crypto-5.3.2.RELEASE.jar;lib\amazon-kinesis-client-2.2.9.jar;lib\commons-lang3-3.10.jar;lib\commons-dbutils-1.7.jar;lib\kinesis-2.10.66.jar;lib\dynamodb-2.10.66.jar;lib\cloudwatch-2.10.66.jar;lib\apache-client-2.10.66.jar;lib\httpclient-4.5.13.jar;lib\avro-1.9.2.jar;lib\commons-csv-1.8.jar;lib\swagger-annotations-2.0.4.jar;lib\commons-io-2.5.jar;lib\log4j-core-2.11.1.jar;lib\log4j-api-2.11.1.jar;lib\kafka-clients-2.5.1.jar;lib\h2-1.4.198.jar;lib\slf4j-nop-1.7.25.jar;lib\rhino-1.7.12.jar;lib\postgresql-42.2.12.jar;lib\commons-dbcp2-2.7.0.jar;lib\jackson-core-asl-1.9.13.jar;lib\javax.ws.rs-api-2.1.1.jar;lib\jsr311-api-1.1.1.jar;lib\jersey-client-2.30.1.jar;lib\bcprov-jdk15on-1.64.jar;lib\lombok-1.18.4.jar;lib\helidon-common-http-2.0.1.jar;lib\helidon-common-reactive-2.0.1.jar;lib\helidon-common-mapper-2.0.1.jar;lib\helidon-common-context-2.0.1.jar;lib\helidon-common-media-type-2.0.1.jar;lib\helidon-common-service-loader-2.0.1.jar;lib\helidon-common-2.0.1.jar;lib\opentracing-util-0.33.0.jar;lib\opentracing-noop-0.33.0.jar;lib\opentracing-api-0.33.0.jar;lib\netty-nio-client-2.10.66.jar;lib\netty-codec-http2-4.1.45.Final.jar;lib\netty-reactive-streams-http-2.0.4.jar;lib\netty-codec-http-4.1.45.Final.jar;lib\netty-reactive-streams-2.0.4.jar;lib\netty-handler-4.1.45.Final.jar;lib\tyrus-server-1.15.jar;lib\tyrus-container-grizzly-client-1.15.jar;lib\tyrus-client-1.15.jar;lib\tyrus-core-1.15.jar;lib\tyrus-spi-1.15.jar;lib\jakarta.websocket-api-1.1.2.jar;lib\yasson-1.0.6.jar;lib\jakarta.json-1.1.6.jar;lib\jakarta.json-1.1.6-module.jar;lib\jersey-common-2.30.1.jar;lib\jakarta.annotation-api-1.3.5.jar;lib\microprofile-health-api-2.1.jar;lib\helidon-health-common-2.0.1.jar;lib\microprofile-metrics-api-2.2.jar;lib\graal-sdk-20.2.0.jar;lib\asm-commons-7.1.jar;lib\asm-util-7.1.jar;lib\asm-analysis-7.1.jar;lib\asm-tree-7.1.jar;lib\asm-7.1.jar;lib\icu4j-67.1.jar;lib\httpcore-4.4.13.jar;lib\commons-logging-1.2.jar;lib\commons-codec-1.11.jar;lib\aws-cbor-protocol-2.10.66.jar;lib\aws-json-protocol-2.10.66.jar;lib\aws-query-protocol-2.10.66.jar;lib\protocol-core-2.10.66.jar;lib\aws-core-2.10.66.jar;lib\auth-2.10.66.jar;lib\regions-2.10.66.jar;lib\sdk-core-2.10.66.jar;lib\jackson-databind-2.10.2.jar;lib\jackson-dataformat-cbor-2.10.0.jar;lib\jackson-core-2.10.2.jar;lib\commons-compress-1.19.jar;lib\http-client-spi-2.10.66.jar;lib\profiles-2.10.66.jar;lib\utils-2.10.66.jar;lib\slf4j-api-1.7.30.jar;lib\zstd-jni-1.4.4-7.jar;lib\lz4-java-1.7.1.jar;lib\snappy-java-1.1.7.3.jar;lib\guava-26.0-jre.jar;lib\protobuf-java-2.6.1.jar;lib\rxjava-2.1.14.jar;lib\commons-pool2-2.7.0.jar;lib\jakarta.ws.rs-api-2.1.6.jar;lib\jakarta.inject-2.6.1.jar;lib\netty-codec-4.1.45.Final.jar;lib\netty-transport-native-epoll-4.1.42.Final-linux-x86_64.jar;lib\netty-transport-native-unix-common-4.1.42.Final.jar;lib\netty-transport-4.1.45.Final.jar;lib\netty-buffer-4.1.45.Final.jar;lib\netty-resolver-4.1.45.Final.jar;lib\netty-common-4.1.45.Final.jar;lib\javax.inject-1.jar;lib\microprofile-config-api-1.4.jar;lib\jakarta.json.bind-api-1.0.2.jar;lib\jackson-annotations-2.10.2.jar;lib\annotations-2.10.66.jar;lib\reactive-streams-1.0.3.jar;lib\jsr305-3.0.2.jar;lib\checker-qual-2.5.2.jar;lib\error_prone_annotations-2.1.3.jar;lib\j2objc-annotations-1.1.jar;lib\animal-sniffer-annotations-1.14.jar;lib\osgi-resource-locator-1.0.3.jar;lib\grizzly-http-server-2.4.4.jar;lib\grizzly-http-2.4.4.jar;lib\grizzly-framework-2.4.4.jar;lib\eventstream-1.0.1.jar

@rem Execute KaDeck
jre\bin\java.exe %DEFAULT_JVM_OPTS% %JAVA_OPTS% %KA_DECK_OPTS%  -classpath "%CLASSPATH%" com.xeotek.kadeck.Application %CMD_LINE_ARGS%

:end
@rem End local scope for the variables with windows NT shell
if "%ERRORLEVEL%"=="0" goto mainEnd

:fail
rem Set variable KA_DECK_EXIT_CONSOLE if you need the _script_ return code instead of
rem the _cmd.exe /c_ return code!
if  not "" == "%KA_DECK_EXIT_CONSOLE%" exit 1
exit /b 1

:mainEnd
if "%OS%"=="Windows_NT" endlocal

:omega