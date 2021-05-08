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
        navigation.setOptions({
            
            title: "Login",
            headerStyle: { backgroundColor: '#2089DC'},
            headerTitleStyle: { color: "#fff", alignSelf: 'center'},
            headerTintColor: 'white',
        });
        

        const unsubscribe = auth.onAuthStateChanged((authUser) => {
            console.log(authUser);
            if(authUser) {
                navigation.replace("Home");
            }
        });
        return unsubscribe;
    }, []);

    const signIn = () => {
        auth
        .signInWithEmailAndPassword(email, password)
        .catch((error) => alert(error));
    }

    return (
        <KeyboardAvoidingView behavior="height" style={styles.container}>
            <StatusBar style='light' />
            <Image source={require('../assets/logo/506.png')} 
                style={{
                    width: 300, 
                    height: 160,
    
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
                    onSubmitEditing={signIn}
                />
            </View>
            <Button containerStyle={styles.button} title="Login" type='solid' 
                    onPress={signIn}
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