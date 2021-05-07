import React, { useState, useEffect } from 'react'
import { StyleSheet, Text, View, KeyboardAvoidingView } from 'react-native'
import { StatusBar } from 'expo-status-bar'
import { Image, Button, Input } from 'react-native-elements'
import { Icon } from 'react-native-elements'
import { auth } from '../firebase'

const LoginScreen = ({ navigation }) => {
    const [email, setEmail] = useState("");
    const [password, setPassword] = useState("");

    useEffect(() => {
        const unsubscribe = auth.onAuthStateChanged((authUser) => {
            console.log(authUser);
            if(authUser) {
                navigation.replace("Home");
            }
        });
        return unsubscribe;
    }, [])

    return (
        <KeyboardAvoidingView behavior="height" style={styles.container}>
            <StatusBar style='light'/>
            <Image source={require('../assets/logo/techs.png')} 
                style={{
                    width:100, 
                    height:100,
                }}
            />
            <View style={styles.inputContainer}>
                <Input
                    style={styles.input}
                    leftIcon={
                        <Icon
                        name='mail'
                        size={20}
                        color='#004052'
                        />
                    }
                    placeholder='Put your fucking email here'
                    value={email}
                    onChangeText={(text) => setEmail(text)}
                />
                <Input
                    style={styles.input}
                    placeholder='Put your fucking password here'
                    leftIcon={
                        <Icon
                        name='lock'
                        size={20}
                        color='#004052'
                        />
                    }
                    secureTextEntry={true}
                    value={password}
                    onChangeText={(text) => setPassword(text)}
                />
            </View>
            <Button containerStyle={styles.button} title="Login" type='solid' 

            />
            <Button onPress={() => navigation.navigate("Register")} containerStyle={styles.button} title="Register" type='outline' 

            />
        </KeyboardAvoidingView>
    )
}

export default LoginScreen

const styles = StyleSheet.create({
    container: {
        flex: 1,
        alignItems: 'center',
        justifyContent: 'center'
    },
    inputContainer: {
        width: 350,
        marginTop: 10,
        
    },
    button: {
        width: 250,
        marginTop: 10,
    },
    input: {
        height: 20,
        padding: 8,
        marginBottom: 1,
    },
});