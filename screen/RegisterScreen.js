import React from 'react'
import { StyleSheet, View, KeyboardAvoidingView } from 'react-native'
import { StatusBar } from 'expo-status-bar'
import { Image, Input, Text, Button } from 'react-native-elements'
import { Icon } from 'react-native-elements'
import { useState, useLayoutEffect } from 'react'
import { auth } from '../firebase'

const RegisterScreen = ({ navigation }) => {
    const [name, setName] = useState("");
    const [email, setEmail] = useState("");
    const [password, setPassword] = useState("");
    const [imageUrl, setimageUrl] = useState("");

    useLayoutEffect(() => {
        navigation.setOptions({
            title: "Register",
            headerStyle: { backgroundColor: '#2089DC'},
            headerTitleStyle: { color: "#fff", alignSelf: 'auto'},
            headerTintColor: 'white',
        });
    }, [navigation]);

    const register = () => {
        auth
            .createUserWithEmailAndPassword(email, password)
            .then((authUser) => {
                authUser.user.updateProfile({
                    displayName: name,
                    photoURL: imageUrl || "https://upload.wikimedia.org/wikipedia/commons/7/7c/Profile_avatar_placeholder_large.png",

                });
            })
            .catch((error) => alert(error.message));
    }



    return (
        <KeyboardAvoidingView behavior='height' style={styles.container}>
            <StatusBar style='light' />
            <Text h4 style={{
                alignSelf:'center',
                marginBottom: 20,
                color : "#2D455E"    
            }}>Create your fucking new account</Text>
            <View style={styles.inputContainer}>
                <Input
                    style={styles.input}
                    leftIcon={
                        <Icon
                        name='user'
                        type='font-awesome'
                        size={20}
                        color='#2D455E'
                        />
                    }
                    type="text"
                    placeholder='Put your fucking name here'
                    value={name}
                    onChangeText = {(text) => setName(text)}
                />
                <Input
                    style={styles.input}
                    leftIcon={
                        <Icon
                        name='mail'
                        size={20}
                        color='#2D455E'
                        />
                    }
                    textContentType="emailAddress"
                    placeholder='Put your fucking email here'
                    value={email}
                    onChangeText = {(text) => setEmail(text)}
                />
                <Input
                    style={styles.input}
                    placeholder='Put your fucking password here'
                    leftIcon={
                        <Icon
                        name='lock'
                        size={20}
                        color='#2D455E'
                        />
                    }
                    textContentType="password"
                    secureTextEntry={true}
                    value={password}
                    onChangeText = {(text) => setPassword(text)}
                />
                <Input
                    style={styles.input}
                    leftIcon={
                        <Icon
                        name='image'
                        type='font-awesome'
                        size={20}
                        color='#2D455E'
                        />
                    }
                    type="text"
                    placeholder="Avatar's URL"
                    value={imageUrl}
                    onChangeText = {(text) => setimageUrl(text)}
                    onSubmitEditing={register}
                />
            </View>
            <Button 
                title="Register" 
                containerStyle={styles.button}
                onPress={register}
            />
            
            <View style={{marginBottom: 80}}/>
        </KeyboardAvoidingView>
    )
}

export default RegisterScreen

const styles = StyleSheet.create({
    container: {
        flex: 1,
        alignItems: 'center',
        justifyContent: 'center'
    },
    button: {
        width: 250,
        marginTop: 10,
        color: '#004052'
    },  
    input: {
        height: -10,
        padding: 8,
        marginBottom: 1,
    },
    inputContainer: {
        width: 325,
        marginTop: 10,
    }
})
